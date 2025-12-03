#Metodo iterativo

import numpy as np
import matplotlib.pyplot as plt

f = lambda x: x-np.cos(x)
g = lambda x: np.cos(x)

x = np.linspace(-1,1,100)
y1 = g(x)
y2 = x
plt.figure()
plt.plot(x,y1,label='g(x)')
plt.plot(x,y2,label='y=x')
plt.title('Metodo iterativo')
plt.show()

#Metodo iterativo

"""def punto_fisso(g, x0):
    k = 0
    while True:
        k += 1
        x1 = g(x0)
        if np.abs(x1 - x0) < 1e-5:
            break
        x0 = x1
    return x1


"""
def punto_fisso(g, f, x0, tol1, tol2, max_iter):
    k = 0
    while (np.abs(f(x0)) > tol1) and (k < max_iter):
        x1 = g(x0)
        cond = np.abs(x0-x1)
        if cond < tol2:
            break
        x0 = x1
        k += 1
        
    return (x1, k)

x0 = 0
sol = punto_fisso(g, f, x0, 1e-6, 1e-5, 100)
print("La soluzione approssimata è:", sol[0])
print("Numero di iterazioni:", sol[1])
