# Metodo di discesa armijo.py

import numpy as np
import matplotlib.pyplot as plt



a = -10
b = 10


xg = np.linspace(a, b)




def taglia_array(array, n):
    return array[:n]


def backtracking_line_search(f, grad, xk):
    alpha = 1
    rho = 0.5
    j = 0
    #pk direzione di crescita
    pk = -grad(xk)

    while f(xk + alpha * pk) > f(xk) + 0.25 * alpha * np.linalg.norm(grad(xk)*pk):
        alpha = rho * alpha
        j = j+1
        if alpha < 1e-10:
            break
    return alpha



def metodo_di_discesa(f, grad, x0, max_iter, x_true, tolf, tolx):
    k = 0
    xk = x0
    errore = np.zeros (max_iter,)
    fun = np.zeros (max_iter,)
    g = np.zeros (max_iter,)
    errore[0] = abs(x_true - x0)
    fun[0] = f(x0)
    g[0] = grad(x0)
    condizione = True

    # Uso il ciclo while per un numero massimo di iterazioni
    while condizione:
        alpha = backtracking_line_search(f, grad, xk)
        x = xk - alpha * grad(xk)
        
        condizione = (k < max_iter) and (np.linalg.norm(grad(xk))**2 > tolf and (np.linalg.norm(x - xk) > tolx))
        xk = x
        errore[k] = abs(x_true - xk)
        fun[k] = f(xk)
        g[k] = abs(grad(xk))
        k = k + 1
        print(f"f(x) = {f(xk)}")
    if k < max_iter:
        errore = taglia_array(errore, k)
        fun = taglia_array(fun, k)
        g = taglia_array(g, k)
    return xk, f(xk), errore, fun, g, k

    

f = lambda x: (x-1)**2 + np.exp (x)
grad = lambda x: 2*(x-1) + np.exp(x)
x0 = 0
x_true = 0.31492 # minimo reale calcolato

max_iter = 100
tolf = 1e-6
tolx = 1e-5
sol, valore, errore, fun, g, k = metodo_di_discesa(f, grad, x0, max_iter, x_true, tolf, tolx)
print(f"Soluzione trovata: x = {sol} in n = {k} iterazioni")
print(f"Errore della soluzione {abs(sol - x_true)}")

plt.plot(errore)
plt.title("Errore in funzione delle iterazioni")
plt.show()

plt.figure()
plt.plot(xg, f(xg), color = 'orange', label='f = x-> (x-1)^2 + exp(x)')
plt.legend()
plt.title("Funzione ")
plt.show()

plt.figure()
plt.plot(fun, 'r', label='f = x-> (x-1)^2 + exp(x)')
plt.legend()
plt.title("Valore della funzione obiettivo in funzione delle iterazioni")
plt.show()

plt.figure()
plt.plot(g, 'g', label='Gradiente')
plt.title("Norma del gradiente in funzione delle iterazioni")
plt.legend()
plt.show()

