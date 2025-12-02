import sys
#print(sys.float_info)
import numpy as np
"""
print(np.spacing(1e9))
print (4.9-4.85)

#con i numeri reali non faccio un confronto di uguaglianza perché potrei avere problemi di approssimazione
#quindi confronto la differenza tra i due numeri con una quantità piccola (epsilon)

esp = np.logspace(0, 16, 17) 
print(esp)

for i in range(0,17):
    s = (1+1/esp[i])**esp[i]
    print("i", i, "err", np.abs(s-np.exp(1)))



from scipy import optimize
f = lambda x: np.cos(x)-x
root = optimize.fsolve(f, -2)
print(root)
print(f(root))
"""
#metodo di bisezione
n = 25
N = tuple(range(0,n+1))

a = 0
b = 2
f = lambda x: x**2 - 2

#iterazioni del for con la tupla N

for i in N:
    c = (a+b)/2
    if f(c)*f(a) < 0:
        b = c
    else:
        a = c

print("soluzione", c)
print("iterazione", i, "soluzione", c, "errore", np.abs(f(c)))