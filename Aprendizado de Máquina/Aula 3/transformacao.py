import pandas as pd

dados = pd.read_csv("../Bases/Pessoa.csv")

categoricoToBinary = pd.get_dummies(dados['Estado_Civil'], prefix='EC')

dados = dados.join(categoricoToBinary)

print(dados)
