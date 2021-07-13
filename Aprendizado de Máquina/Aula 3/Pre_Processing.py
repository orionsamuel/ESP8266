import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from sklearn.impute import SimpleImputer
from sklearn.compose import make_column_transformer
from sklearn.neighbors import LocalOutlierFactor
from sklearn.preprocessing import MinMaxScaler
from sklearn.neighbors import KNeighborsRegressor
from sklearn.model_selection import RepeatedKFold
from sklearn.metrics import mean_squared_error

dados = pd.read_csv("melb_data.csv")

dados.head()

"""# Eliminação de atributos descartavéis e tratamento dos valores faltosos"""

discard = ["SellerG", "Address", "Lattitude", "Longtitude"]

X = dados.drop(discard, axis = 1)

X.isna().sum()

X = X.dropna(subset=["Car"])

mean_imputer = SimpleImputer()
mostFrequent_imputer = SimpleImputer(strategy='most_frequent')

mean_transformer = make_column_transformer(
                                           (mean_imputer, ["BuildingArea", "YearBuilt"]),
                                           (mostFrequent_imputer, ["CouncilArea"]),
                                           remainder="drop"
                                           )

X_mean = pd.DataFrame(mean_transformer.fit_transform(X), columns=["BuildingArea", "YearBuilt", "CouncilArea"], index=X.index)

X = pd.merge(X,X_mean)

X.isna().sum()

"""# Geração de gráficos para visualização primária dos dados"""

numerical = ['Rooms', 'Price', 'Distance', 'Bedroom2', 'Bathroom', 'Landsize', 'BuildingArea', 'YearBuilt', 'Propertycount']

for item in numerical:
  plt.figure(figsize=(16, 8), dpi=80)
  plt.ylabel(item)
  plt.xlabel('Date')
  plt.scatter(X['Date'], X[item])
  plt.show()

"""# Tratamento dos outilers"""

clf = LocalOutlierFactor()

numerical = ['Price', 'Distance', 'Landsize', 'BuildingArea', 'YearBuilt', 'Propertycount']

X_predicted = X[numerical]

predicted = pd.Series(clf.fit_predict(X_predicted), name="predicted", index=X_predicted.index)

X_predicted = pd.concat([X_predicted, predicted], axis=1)

print(X_predicted.query("predicted == -1"))

X = X.drop(X_predicted.query("predicted == -1").index)

"""# Geração de gráficos para visualização pós tratamento dos dados"""

for item in numerical:
  plt.figure(figsize=(16, 8), dpi=80)
  plt.ylabel(item)
  plt.xlabel('Date')
  plt.scatter(X['Date'], X[item])
  plt.show()

"""# Transformação dos dados """

Suburb = pd.get_dummies(X['Suburb'], prefix = 'Sub')
Type = pd.get_dummies(X['Type'], prefix = 'T')
Method = pd.get_dummies(X['Method'], prefix = 'Met')
Council = pd.get_dummies(X['CouncilArea'], prefix = 'CA')
Region = pd.get_dummies(X['Regionname'], prefix = 'RN')

X = X.join(Type)
X = X.join(Method)
X = X.join(Council)
X = X.join(Region)
X = X.join(Suburb)

X = X.drop(['Suburb', 'Type', 'Method', 'CouncilArea', 'Regionname', 'Date'], axis = 1)

X.head()

numerical = ['Rooms', 'Distance', 'Bedroom2', 'Bathroom', 'Landsize', 'BuildingArea', 'YearBuilt', 'Propertycount']

for item in numerical:
  X[item] = (X[item] - X[item].min()) / (X[item].max() - X[item].min())

X.head()

X.to_csv("melb_data_tratada.csv", sep=',', index=False)
