import pandas as pd
from sklearn.model_selection import RepeatedKFold
from sklearn.metrics import accuracy_score, confusion_matrix
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split

dados = pd.read_csv('../Bases/diabetes.csv')

X = dados.iloc[:,:-1].values
y = dados.iloc[:,-1].values

#X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.3, random_state = 1)

rkf = RepeatedKFold(n_splits=10, n_repeats=10, random_state=990)

for train, test in rkf.split(X, y):
    X_train = X[train]
    X_test = X[test]
    y_train = y[train]
    y_test = y[test]

ad = DecisionTreeClassifier()

ad.fit(X_train, y_train)

y_pred = ad.predict(X_test)

acc = str(accuracy_score(y_test, y_pred))

print("Acurácia:", acc)

cm = confusion_matrix(y_test, y_pred)

print("Matriz de confusão")
print(cm)