# Metodo di discesa armijo.py

import numpy as np
import matplotlib.pyplot as plt

def backtracking_line_search(f, grad, xk):
    """
    Esegue la ricerca del passo tramite il metodo di backtracking.

    :param f: La funzione da minimizzare.
    :param grad: La funzione che calcola il gradiente della funzione da minimizzare.
    :param xk: Il punto corrente.
    :return: La dimensione del passo trovata.
    """
    alpha = 1
    rho = 0.5
    j = 0
    #pk direzione di crescita
    pk = -grad(xk)

    while f(xk + alpha * pk) > f(xk) + 0.25 * alpha * np.linalg.norm(grad(xk)*pk):
        alpha = rho * alpha
        j = j+1
    return alpha




def metodo_di_discesa(f, grad, x0, max_iter, x_true):
    """
    Esegue il metodo di discesa per minimizzare una funzione.

    :param f: La funzione da minimizzare.
    :param grad: La funzione che calcola il gradiente della funzione da minimizzare.
    :param x0: Il punto di partenza per la discesa.
    :param alpha: La dimensione del passo per ogni iterazione.
    :param e: La tolleranza per la convergenza.
    :param max_iter: Il numero massimo di iterazioni.
    :param x_true: Il valore vero del minimo per il calcolo dell'errore (opzionale).
    :return: Il punto minimo trovato e il valore della funzione in quel punto, il numero di iterazioni eseguite, l'array degli errori e l'array dei valori della funzione.
    """
    k = 0
    xk = x0
    errore = np.zeros (max_iter,)
    fun = np.zeros (max_iter,)
    g = np.zeros (max_iter,)
    errore[0] = abs(x_true - x0)
    fun[0] = f(x0)
    g[0] = grad(x0)
    
    # Uso il ciclo for per un numero massimo
    while k < max_iter:
        alpha = backtracking_line_search(f, grad, xk)
        x = xk - alpha * grad(xk)

        #if abs(f(x) - f(xk)) < 1e-6:
         #   break

        xk = x
        errore[k] = abs(x_true - xk)
        fun[k] = f(xk)
        g[k] = abs(grad(xk))
        k = k + 1

    return xk, f(xk), errore, fun, g, k

    

f = lambda x: (x-1)**2 + np.exp (x)
grad = lambda x: 2*(x-1) + np.exp(x)
x0 = 0
x_true = 0.31492 # minimo reale calcolato

max_iter = 100

sol, valore, errore, fun, g, k = metodo_di_discesa(f, grad, x0, max_iter, x_true)
print(f"Soluzione trovata: x = {sol} in n = {k} iterazioni")
print(f"Errore della soluzione {abs(sol - x_true)}")

plt.plot(errore)
plt.show()

plt.figure()
plt.plot(fun, 'r')
plt.show()

plt.figure()
plt.plot(g, 'g')
plt.show()

