import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np

nyc_airbnb = pd.read_csv('../Bases/AB_NYC_2019.csv')

numerical = ["price", "minimum_nights","number_of_reviews", 
             "calculated_host_listings_count", "availability_365"]

nyc_airbnb.loc[:,numerical] = nyc_airbnb[numerical].apply(np.log1p, axis = 1)

#sns.displot(nyc_airbnb["price"], bins = 100)

from sklearn.neighbors import LocalOutlierFactor

clf = LocalOutlierFactor()

X_num = nyc_airbnb[numerical]

predicted = pd.Series(clf.fit_predict(X_num), name="predicted", index=X_num.index)

X_predicted = pd.concat([X_num, predicted], axis=1)

X_outliers = X_predicted.query("predicted == -1")

print(X_outliers)

nyc_airbnb = nyc_airbnb.drop(X_predicted.query("predicted == -1").index)
