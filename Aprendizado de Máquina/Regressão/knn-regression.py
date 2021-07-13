import pandas as pd
import numpy as np
from sklearn.neighbors import KNeighborsRegressor
from sklearn.model_selection import RepeatedKFold

def mean_absolute_percentage_error(y_true, y_pred): 
    y_true, y_pred = np.array(y_true), np.array(y_pred)
    return np.mean(np.abs((y_true - y_pred) / y_true)) * 100

dados = pd.read_csv("melb_data_tratada.csv")

target = dados['Price'].copy()
dados = dados.drop(['Price'], axis = 1)

X = dados.iloc[:,:].values
target = target.iloc[:].values

rkf = RepeatedKFold(n_splits=10, n_repeats=10, random_state=990)

for train, test in rkf.split(X, target):
    X_train = X[train]
    X_test = X[test]
    target_train = target[train]
    target_test = target[test]

mape_val = []

for K in range(20):
    K = K + 1
    knn = KNeighborsRegressor(n_neighbors=K, metric='euclidean')
    knn.fit(X_train, target_train)
    target_pred = knn.predict(X_test)
    err = str(mean_absolute_percentage_error(target_test, target_pred))
    mape_val.append(err)
    print("Erro MAPE para o valor de K = ", K, ": ", err)
