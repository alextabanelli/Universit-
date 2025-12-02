# Metodo di discesa armijo con criteri di arresto ad 2 variabili

import numpy as np
import matplotlib.pyplot as plt

# 1️⃣ Definizione della funzione
f = lambda x, y: (x)**2 + 3*(y)**2
grad = lambda x, y: np.array([2*x, 6*y])

# 2️⃣ Creazione griglia di punti
x = np.linspace(-5, 5, 100)
y = np.linspace(-5, 5, 100)
X, Y = np.meshgrid(x, y)
Z = f(X, Y)



max_iter = 100
tolf = 1e-6
tolx = 1e-5

s = 6

alfa = -s
beta = s

p0 = [1,1]


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



def metodo_di_discesa(f, grad, p0, max_iter, tolf, tolx):

    # Creo il grafico 3D in una solo pagina, senza subplot
    fig = plt.figure(figsize=(12, 5))
    ax = fig.add_axes([0, 0, 1, 1], projection='3d')
    surf = ax.plot_surface(X, Y, Z, cmap='plasma', edgecolor='none')  # plotsurface crea la superficie 3D (X, Y, Z)
    ax.set_title("Superficie 3D di f(x, y) = x² + y²")
    ax.set_xlabel("x")
    ax.set_ylabel("y")
    ax.set_zlabel("f(x, y)")
    plt.show()



    fig = plt.figure(figsize=(12, 5))
    ax1 = fig.add_subplot(1, 2, 2)  # subplot diviso in 1 riga, 2 colonne, 2° subplot
    contours = ax1.contour(X, Y, Z, levels=30, cmap='coolwarm')
    ax1.clabel(contours, inline=True, fontsize=8)
    ax1.set_title("Curve di livello di f(x, y) = x² + y²")
    ax1.set_xlabel("x")
    ax1.set_ylabel("y")
    ax1.axis("equal")

    # 🔹 Subplot 2 — Superficie 3D
    ax2 = fig.add_subplot(1, 2, 1, projection='3d') # subplot diviso in 1 riga, 2 colonne, 1° subplot
    surf = ax2.plot_surface(X, Y, Z, cmap='plasma', edgecolor='none')  # plotsurface crea la superficie 3D (X, Y, Z)
    ax2.set_title("Superficie 3D di f(x, y) = x² + y²")
    ax2.set_xlabel("x")
    ax2.set_ylabel("y")
    ax2.set_zlabel("f(x, y)")
    fig.colorbar(surf, ax=ax2, shrink=0.5, aspect=10, label='f(x, y)')

    # 4️⃣ Mostra tutto insieme
    plt.tight_layout() # tight_layout serve per evitare sovrapposizioni tra i subplot
    plt.show()

    k = 0
    xk = p0
    # definisco gli array di coppie
    fun = np.zeros((max_iter,))
    g = np.zeros((max_iter,))
    fun[0] = f(p0[0],p0[1])
    g[0] = grad(p0[0],p0[1])
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
    sol, valore, fun, g, k = metodo_di_discesa(f, grad, p0, max_iter, tolf, tolx)
    print(f"Soluzione trovata: x = {sol} in n = {k} iterazioni")

homework2()