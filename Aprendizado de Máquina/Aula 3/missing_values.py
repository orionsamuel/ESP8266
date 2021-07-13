import pandas as pd

nyc_airbnb = pd.read_csv('../Bases/AB_NYC_2019.csv')

#print(nyc_airbnb)

discard = ["id", "last_review"]

X = nyc_airbnb.drop(discard, axis = 1)

#print(X.isna().sum())

X = X.dropna(subset=["name", "host_name"])

#print(X.isna().sum())

from sklearn.impute import SimpleImputer
mean_imputer = SimpleImputer()

from sklearn.compose import make_column_transformer
mean_transformer = make_column_transformer(
                                           (mean_imputer, ["reviews_per_month"]),
                                           remainder="drop"
                                           )

X_mean = pd.DataFrame(mean_transformer.fit_transform(X), columns=["reviews_per_month"], index=X.index)

#print(X_mean.isna().sum())

