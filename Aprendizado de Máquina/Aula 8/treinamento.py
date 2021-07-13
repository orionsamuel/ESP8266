import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.model_selection import KFold

dados = pd.read_csv('../Bases/diabetes.csv')

X = dados.iloc[:,:-1].values
y = dados.iloc[:,-1].values

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.3, random_state = 1)

kf = KFold(n_splits = 10)

for train, test in rkf.split(X, y):
    X_train2 = X[train]
    X_test2 = X[test]
    y_train2 = y[train]
    y_test2 = y[test]
