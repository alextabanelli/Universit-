#Metodo di Newton

import numpy as np
import matplotlib.pyplot as plt

f = lambda x: x-np.cos(x)
df = lambda x: 1+np.sin(x)

def newton(f, df, x0, tol1, tol2, max_iter):
    k = 0
    while (np.abs(f(x0)) > tol1) and (k < max_iter):
        x1 = x0 - f(x0)/df(x0)
        if np.abs(x1 - x0) < tol2:
            break
        x0 = x1
        k += 1
    return x0, k   

x0 = 0
sol = newton(f, df, x0, 1e-6, 1e-5, 100)
print("Soluzione approssimata:", sol[0])
print("Numero di iterazioni:", sol[1])
        