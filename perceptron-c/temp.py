import numpy as np
import matplotlib.pyplot as pl

data = np.genfromtxt("dataset/X.csv", dtype=float, delimiter=';')[:,:2]
y = np.genfromtxt("dataset/y_true.csv", dtype=int)

colors = ['blue', 'red']

x = np.array([(i- 500) / 50.0  for i in range(1000)])
pl.plot(x, 1 / (1 + np.exp(-x)))
pl.show()