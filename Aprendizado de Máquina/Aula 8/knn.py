import pandas as pd
from sklearn.model_selection import RepeatedKFold
from sklearn.metrics import accuracy_score, confusion_matrix, precision_score, recall_score, f1_score
from sklearn.neighbors import KNeighborsClassifier

#Lendo os dados
dados = pd.read_csv('../Bases/diabetes.csv')

#Separando os dados das classes
X = dados.iloc[:,:-1].values
y = dados.iloc[:,-1].values

#Gerando a divisão
rkf = RepeatedKFold(n_splits=10, n_repeats=10, random_state=1)

#Loop para percorrer os folds
for train, test in rkf.split(X, y):
    X_train = X[train]
    X_test = X[test]
    y_train = y[train]
    y_test = y[test]

#Criando o modelo
knn = KNeighborsClassifier(n_neighbors=2, metric='euclidean')

knn.fit(X_train, y_train)

#Prevendo a resposta para o conjunto de testes
y_pred = knn.predict(X_test)

#Acurácia do modelo
acc = str(accuracy_score(y_test, y_pred))

print("Acurácia: ", acc)

#Precisão do modelo
prec = str(precision_score(y_test, y_pred, average = 'macro'))

print("Precisão: ", prec)

#Recall do modelo
rec = str(recall_score(y_test, y_pred, average = 'macro'))

print("Recall: ", rec)

#F1 score do modelo
f1 = str(f1_score(y_test, y_pred, average = 'macro'))

print("F1 Score: ", f1)

#Matriz de confusão
cm = confusion_matrix(y_test, y_pred)

print("Matriz de confusão")
print(cm)
