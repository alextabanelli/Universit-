# Metodo di discesa armijo con criteri di arresto ad una variabile

import numpy as np
import matplotlib.pyplot as plt

f = lambda x: (x-1)**2 + np.exp (x)
grad = lambda x: 2*(x-1) + np.exp(x)
x0 = 5

max_iter = 100
tolf = 1e-6
tolx = 1e-5

s = 6

alfa = -s
beta = s


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



def metodo_di_discesa(f, grad, x0, max_iter, tolf, tolx):

    xg = np.linspace(alfa, beta)
    plt.figure(figsize=(8, 8))
    plt.title ("Grafico della funzione obiettivo")
    plt.plot (xg, f(xg), color = 'orange', label='f = (x-1)^2 + exp(x)')
    plt.plot(x0, f(x0), 'ro', label='Punto iniziale')
    plt.legend()
    plt.grid()
    plt.show()

    xg = np.linspace(alfa, beta, 400)
    plt.figure(figsize=(8, 8))
    plt.title ("Metodo di discesa con backtracking")
    plt.plot (xg, f(xg), color = 'orange', label='f = (x-1)^2 + exp(x)')
    plt.legend()


    k = 0
    xk = x0
    fun = np.zeros (max_iter,)
    g = np.zeros (max_iter,)
    fun[0] = f(x0)
    g[0] = grad(x0)
    condizione = True

    # Uso il ciclo while per un numero massimo di iterazioni
    while condizione:
        alpha = backtracking_line_search(f, grad, xk)
        x = xk - alpha * grad(xk)
        
        condizione = (k < max_iter) and (np.linalg.norm(grad(xk))**2 > tolf and (np.linalg.norm(x - xk) > tolx))
        xk = x
        plt.plot(x, f(x), 'ro')
        fun[k] = f(xk)
        g[k] = abs(grad(xk))
        k = k + 1
        # print(f"f(x) = {f(xk)}")

    if k < max_iter:
        print(f"f(x) = {f(xk)}")
        print(f"Convergenza raggiunta dopo {k} iterazioni")
        plt.plot(xk, f(xk), 'yo', label='Convergenza')
        fun = taglia_array(fun, k)
        g = taglia_array(g, k)

    d = 2
    plt.xlim(-0.5, 1)  
    plt.ylim(1.5, 4)
    plt.grid()
    plt.legend()   
    plt.show()


    plt.figure()
    plt.plot(fun, 'r', label='f = x-> (x-1)^2 + exp(x)')
    plt.title("Valore della funzione obiettivo in funzione delle iterazioni")
    plt.xlabel("Iterazioni")
    plt.ylabel("f(x)")
    plt.grid()
    plt.legend()
    plt.show()

    plt.figure()
    plt.plot(g, 'g', label='Gradiente')
    plt.title("Norma del gradiente in funzione delle iterazioni")
    plt.xlabel("Iterazioni")
    plt.ylabel("||g(x)||")
    plt.grid()
    plt.legend()
    plt.show()

    
    return xk, f(xk), fun, g, k




def homework2():
    sol, valore, fun, g, k = metodo_di_discesa(f, grad, x0, max_iter, tolf, tolx)
    print(f"Soluzione trovata: x = {sol} in n = {k} iterazioni")

homework2()