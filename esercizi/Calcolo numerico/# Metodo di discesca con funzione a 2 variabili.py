# Metodo di discesca con funzione a 2 variabili

import numpy as np
import matplotlib.pyplot as plt

# 1️⃣ Definizione della funzione
f = lambda x, y: (x) + 3*(y)**2
grad = lambda x, y: np.array([1, 6*y])

# 2️⃣ Creazione griglia di punti
x = np.linspace(-5, 5, 100)
y = np.linspace(-5, 5, 100)
X, Y = np.meshgrid(x, y)
Z = f(X, Y)

max_iter = 100
tolf = 1e-6
tolx = 1e-6

r = 6

alfa = -r
beta = r

p0 = [5,-3]


def taglia_array(array, n):
    return array[:n]



def backtracking_line_search(f, grad, xk):
    alpha = 1
    rho = 0.5
    j = 0
    #pk direzione di crescita
    pk = [0,0]
    pk[0], pk[1] = -grad(xk[0],xk[1])

    while f(xk[0]+alpha*pk[0], xk[1]+alpha*pk[1]) > f(xk[0], xk[1]) + 0.25 * alpha * np.linalg.norm(pk)**2:
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

    # 🔹 Subplot 1 — Curve di livello
    fig = plt.figure(figsize=(12, 5))
    ax1 = fig.add_subplot(1, 2, 2)  # subplot diviso in 1 riga, 2 colonne, 2° subplot
    contours = ax1.contour(X, Y, Z, levels=15, cmap='coolwarm')
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

    k = 0
    xk = p0
    # Segno il punto iniziale
    ax1.plot(p0[0], p0[1], 'go', label = "Punto iniziale")
    ax2.plot([p0[0]], [p0[1]], [f(p0[0], p0[1])], marker='o', color='orange',
            markersize=8, markeredgecolor='k', zorder=10, label='Punto iniziale')
    # definisco gli array di coppie
    fun = np.zeros(max_iter)
    g = np.zeros((max_iter, 2))
    fun[0] = f(p0[0],p0[1])
    g[0][0], g[0][1] = grad(p0[0],p0[1])
    condizione = True
    x = [0,0]
    xk[0], xk[1] = p0
    # Uso il ciclo while per un numero massimo di iterazioni
    while condizione:
        alpha = backtracking_line_search(f, grad, p0)
        x[0], x[1] = (xk[0] - alpha * grad(xk[0], xk[1])[0]) , (xk[1] - alpha * grad(xk[0], xk[1])[1])
        ax1.plot([xk[0], x[0]],[xk[1], x[1]], 'y-')
        #print(f"Value x: {x}")
        #print(f"Value xk: {xk}")
        #print(f"Cn1: {np.linalg.norm(grad(xk[0], xk[1]))**2}")
        #print(f"Cn2: {np.linalg.norm((x[0] - xk[0], x[1] - xk[1]))}")

        condizione = (k < max_iter) and (np.linalg.norm(grad(xk[0], xk[1]))**2 > tolf and (np.linalg.norm((x[0] - xk[0], x[1] - xk[1])) > tolx))
        if condizione:
            xk[0], xk[1] = x
            # Segno il punto xk nel grafico per vedere l'andamento dell'algoritmo
            ax1.plot(xk[0], xk[1], 'ro')
            fun[k] = f(xk[0], xk[1])
            g[k][0], g[k][1] = abs(grad(xk[0], xk[1]))
            k = k + 1
        # print(f"f(x) = {f(xk)}")

    if k < max_iter:
        fun = taglia_array(fun, k)
        g = taglia_array(g, k)


    print(f"f(x) = {f(xk[0], xk[1])}")
    print(f"Convergenza raggiunta dopo {k} iterazioni")
    # Segno la convergenza nel sottografico con le linee di livello
    ax1.plot(xk[0], xk[1], 'yo', label='Convergenza')
    # Segno la convergenza nel sottografico 3D
    ax2.plot([xk[0]], [xk[1]], [f(xk[0], xk[1])], marker='o', color='red',
            markersize=8, markeredgecolor='k', zorder=10, label='Punto di Convergenza')    
    ax1.legend()
    ax2.legend()
    plt.show()
    # Zoom automatico per vedere meglio il punto di convergenza
    #m = 1.2
    #ax1.set_xlim(-m, m)
    #ax1.set_ylim(-m, m)
    #plt.show()

    # Andamento della funzione obiettivo
    plt.figure()
    plt.plot(fun[:k])
    plt.title("Andamento della funzione obiettivo")
    plt.xlabel("Iterazione")
    plt.ylabel("f(x)")
    plt.grid()
    plt.show()

    # Andamento del gradiente
    plt.figure()
    plt.plot(np.linalg.norm(g[:k], axis=1))
    plt.title("Andamento del gradiente")
    plt.xlabel("Iterazione")
    plt.ylabel("||∇f(x)||")
    plt.grid()
    plt.show()

    return xk, f(xk[0], xk[1]), fun, g, k



sol, valore, fun, g, k = metodo_di_discesa(f, grad, p0, max_iter, tolf, tolx)