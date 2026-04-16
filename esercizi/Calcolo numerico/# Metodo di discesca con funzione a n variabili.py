# Metodo di discesca con funzione a n
#  variabili

import numpy as np
import matplotlib.pyplot as plt


def taglia_array(array, n):
    return array[:n]

def backtracking_line_search(f, grad, xk):


    """
    Esegue la ricerca di linea (Armijo) per funzioni n-dimensionali.
    """
    alpha = 1.0
    rho = 0.5
    c = 1e-4  # Costante tipica per Armijo (0.25 nel tuo codice originale è ok, ma 1e-4 è standard)
    
    # Calcolo valore funzione e gradiente al punto corrente
    fk = f(xk)
    grad_k = grad(xk)
    
    # Condizione di Armijo generalizzata: f(xk + alpha*pk) <= f(xk) + c * alpha * grad(xk)^T * pk
    # Nota: pk è la direzione di discesa (solitamente -grad_k)
    # Assegno a pk -grad_k
    pk = -grad_k
    
    while f(xk + alpha * pk) > fk + c * alpha * np.dot(grad_k, pk):
        alpha = alpha * rho
        if alpha < 1e-10:
            break
    return alpha

def metodo_di_discesa(f, grad, p0, max_iter=100, tolf=1e-6, tolx=1e-6):
    
    # Assicuriamoci che p0 sia un array numpy float
    xk = np.array(p0, dtype=float)
    n = len(xk)  # Dimensione del problema
    
    # Inizializzazione storici
    history_x = [xk.copy()] # Salviamo la traiettoria dei punti
    history_f = [f(xk)]
    history_grad_norm = [np.linalg.norm(grad(xk))]
    
    # SETUP GRAFICO SOLO SE N=2
    if n == 2:
        # 2️⃣ Creazione griglia di punti
        x = np.linspace(-5, 5, 100)
        y = np.linspace(-5, 5, 100)
        X, Y = np.meshgrid(x, y)
        Z = f(np.array([X, Y]))
        # Creo il grafico 3D in una solo pagina, senza subplot
        fig = plt.figure(figsize=(12, 5))
        ax = fig.add_axes([0, 0, 1, 1], projection='3d')
        surf = ax.plot_surface(X, Y, Z, cmap='plasma', edgecolor='none')  # plotsurface crea la superficie 3D (X, Y, Z)
        ax.set_title("Superficie 3D di f(x, y) = x² + y²")
        ax.set_xlabel("x")
        ax.set_ylabel("y")
        ax.set_zlabel("f(x, y)")
        plt.show()
        
        # Subplot 1: Superficie 3D
        fig = plt.figure(figsize=(12, 5))
        ax1 = fig.add_subplot(1, 2, 1, projection='3d')
        surf = ax1.plot_surface(X, Y, Z, cmap='plasma', alpha=0.8, edgecolor='none')
        ax1.set_title("Superficie 3D")
        ax1.set_xlabel("x1")
        ax1.set_ylabel("x2")
        ax1.set_zlabel("f(x)")
        
        # Subplot 2: Curve di livello
        ax2 = fig.add_subplot(1, 2, 2)
        contours = ax2.contour(X, Y, Z, levels=20, cmap='coolwarm')
        ax2.clabel(contours, inline=True, fontsize=8)
        ax2.set_title("Curve di livello e Traiettoria")
        ax2.set_xlabel("x1")
        ax2.set_ylabel("x2")
        ax2.axis("equal")
        
        # Plot punto iniziale
        ax2.plot(xk[0], xk[1], 'go', label="Start")
        #ax1.scatter(xk[0], xk[1], f(xk), color='green', s=50, label='Start')
        ax1.plot([xk[0]], [xk[1]], [f(xk)], marker='o', color='red',
            markersize=8, markeredgecolor='k', zorder=10, label='Punto di Convergenza') 

    # LOOP DI OTTIMIZZAZIONE
    k = 0
    condizione = True
    
    while condizione and k < max_iter:
        grad_k = grad(xk)
        pk = -grad_k  # Direzione di discesa (Antigradiente)
        
        # Calcolo alpha con backtracking
        alpha = backtracking_line_search(f, grad, xk)
        
        # Aggiornamento xk+1
        xk_new = xk + alpha * pk
        
        # Calcolo metriche per stop
        norm_grad = np.linalg.norm(grad_k)
        step_norm = np.linalg.norm(xk_new - xk)
        
        # Salvataggio dati
        history_x.append(xk_new.copy())
        history_f.append(f(xk_new))
        history_grad_norm.append(np.linalg.norm(grad(xk_new)))
        
        # Aggiornamento grafico "live" (solo traiettoria) se n=2
        # Nota: aggiornare i plot dentro il loop rallenta molto, 
        # qui plotto solo i segmenti
        if n == 2:
            ax2.plot([xk[0], xk_new[0]], [xk[1], xk_new[1]], 'y.-')
        
        # Controllo convergenza
        # Nota: La tua condizione originale richiedeva CHE ENTRAMBI (grad e step)
        # fossero sopra la soglia per continuare. 
        # Solitamente ci si ferma se ALMENO UNO è sotto la soglia.
        # Qui mantengo la logica originale: continuo finché gradient è alto E passo è lungo.
        condizione = (norm_grad > tolf) and (step_norm > tolx)
        
        xk = xk_new
        k += 1

    # FINE LOOP - FINALIZZAZIONE GRAFICI
    print(f"Convergenza raggiunta dopo {k} iterazioni")
    print(f"Punto finale: {xk}")
    print(f"Valore finale f(x): {history_f[-1]}")

    if n == 2:
        # Segna punto finale
        ax2.plot(xk[0], xk[1], 'ro', label='End')
        ax1.scatter(xk[0], xk[1], history_f[-1], color='red', s=50, label='End')
        ax2.legend()
        plt.tight_layout()
        plt.show()

    # Grafici di analisi (validi per qualsiasi n)
    # Andamento della funzione obiettivo
    plt.figure()
    plt.plot(history_f)
    plt.title("Andamento della funzione obiettivo")
    plt.xlabel("Iterazione")
    plt.ylabel("f(x)")
    plt.grid()
    plt.show()

    # Andamento del gradiente
    plt.figure()
    plt.plot(history_grad_norm)
    plt.title("Andamento del gradiente")
    plt.xlabel("Iterazione")
    plt.ylabel("||∇f(x)||")
    plt.grid()
    plt.show()

    return xk, history_f[-1], np.array(history_f), np.array(history_grad_norm), k

# --- ESEMPIO DI UTILIZZO ---

# 1️⃣ Definizione della funzione
def f_c(x):
    return x[0]**2 + 3*x[1]**2 + x[2]**2

def grad_c(x):
    return np.array([2*x[0], 6*x[1], 2*x[2]])


max_iter = 5000
tolf = 1e-6
tolx = 1e-6


p0 = [5,-3, 6]

metodo_di_discesa(f_c, grad_c, p0, max_iter, tolf, tolx)
