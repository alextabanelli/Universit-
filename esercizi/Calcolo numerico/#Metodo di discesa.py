# Metodo di discesa

import numpy as np
import matplotlib.pyplot as plt

def metodo_di_discesa(f, grad, x0, alpha, max_iter, x_true):
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

    xk = x0
    errore = np.zeros (max_iter,)
    fun = np.zeros (max_iter,)
    g = np.zeros (max_iter,)
    errore[0] = abs(x_true - x0)
    fun[0] = f(x0)
    g[0] = grad(x0)
    
    # Uso il ciclo for per un numero massimo
    for i in range(max_iter):

        x = xk - alpha * grad(xk)

        #if abs(f(x) - f(xk)) < 1e-6:
         #   break

        xk = x
        errore[i] = abs(x_true - xk)
        fun[i] = f(xk)
        g[i] = abs(grad(xk))
        #print(f"gradiente = {grad(xk)}")

    return xk, f(xk), errore, fun, g


    """
    #Uso un ciclo while per la convergenza
    
    k = 0
    while k < max_iter:
        grad = grad(xk)
        x = xk - alpha * grad

        if abs(f(x) - f(xk)) < e:
            break

        xk = x

        k += 1

    return xk, f(xk)

    """

f = lambda x: (x-1)**2 + np.exp (x)
grad = lambda x: 2*(x-1) + np.exp(x)
alpha = 1.0e-2
x0 = 0
x_true = 0.31492 # minimo reale calcolato

max_iter = 200

sol, valore, errore, fun, g = metodo_di_discesa(f, grad, x0, alpha, max_iter, x_true)
print(f"Soluzione trovata: x = {sol} in n = {max_iter} iterazioni")
print(f"Errore della soluzione {abs(sol - x_true)}")

plt.plot(errore)
plt.show()

plt.figure()
plt.plot(fun, 'r')
plt.show()

plt.figure()
plt.plot(g, 'g')
plt.show()

