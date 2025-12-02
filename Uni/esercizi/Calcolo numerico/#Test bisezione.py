#Test bisezione

import numpy as np
import matplotlib.pyplot as plt

a = -1
b = 1

x = np.linspace(a, b, 100)
y = x-np.cos(x)

# Visualizzazione
plt.figure()
plt.plot(x, y)
y1 = np.zeros(len(x))
plt.plot(x, y1, color='red')
plt.show()

#Metodo della bisezione

N = 15 #numero di iterazioni

f = lambda x: x-np.cos(x)
def bisezione(f, a, b, N):
    if f(a)*f(b) > 0:
        print("Non c'è il cambio di segno")
        return None
    for n in range(N):
        c = (a+b)/2
        if f(c) == 0:
            print("Trovata soluzione esatta")
            return c
        elif f(a)*f(c) < 0:
            b = c
        else:
            a = c
    print("Soluzione approssimata dopo", N, "iterazioni")
    return (a+b)/2

sol = bisezione(f, a, b, N)
print("La soluzione approssimata è:", sol)
