import numpy as np
import matplotlib.pyplot as plt


# Funzione da analizzare
# e^x − 3x
f = lambda x: x*x - np.cos(x)
df = lambda x: 2*x + np.sin(x)
g = lambda x: np.sqrt(np.cos(x))

alfa = -8
beta = 8







# Parametri comuni
max_iter = 100
# Epsilon
epsilon = 1e-3
epsilon1 = 1e-3
epsilon2 = 1e-3
# Punto iniziale
x0 = 0.8
# Intervallo
a = 0
b = 1

x = np.linspace(alfa, beta, 100)
plt.figure(figsize=(8, 4))
plt.subplot(1, 2, 1)
plt.title ("Funzione f(x) = x^2 - cos(x)")
plt.plot (x, f(x), 'g', label='y = f(x)')


y = np.zeros_like(x)
plt.plot(x, y, 'yellow', label='y = 0')


d = 6
plt.xlim(-d, d)  # mostra solo l'intervallo [-10, 10] sull'asse x
plt.ylim(-d, d)   # mostra solo l'intervallo [-10, 10] sull'asse y
plt.legend()
plt.grid()

plt.subplot(1, 2, 2)
x = np.linspace(alfa, beta, 100)
plt.title ("Funzione g(x) = sqrt(cos(x))")
plt.plot (x, g(x), 'orange', label='y = g(x)')
d = 10
plt.xlim(-d, d)  # mostra solo l'intervallo [-10, 10] sull'asse x
plt.ylim(-2, 2)   # mostra solo l'intervallo [-10, 10] sull'asse y
plt.legend()
plt.grid()
plt.show()




def metodo_bisezione(f, a, b, max_iter, epsilon):
    # Stampa metodo di bisezione
    x = np.linspace(a, b)
    plt.figure(figsize=(12, 4))
    plt.subplot(1, 3, 1)
    plt.title ("Metodo di Bisezione")
    plt.plot (x, f(x), 'b')
    y = np.zeros_like(x)
    plt.plot(x, y, 'yellow', label='y = 0')
    plt.xlim(a, b)  # mostra solo l'intervallo [-6, 1] sull'asse x
    if f(a) < f(b):
        plt.ylim(f(a), f(b))   # mostra solo l'intervallo [f(-6), f(1)] sull'asse y
    else:
        plt.ylim(f(b), f(a))   # mostra solo l'intervallo [f(-6), f(1)] sull'asse y
    # Metodo di bisezione
    fk = np.zeros(max_iter)
    cn = True
    cond = True
    i = 0
    print("\nMetodo di Bisezione:")
    print(f"a = {a}, b = {b}")
    if f(a) * f(b) >= 0.0:
        print("Il metodo di bisezione non può essere applicato.")
        return None, 0
    while cond and i < max_iter:
        c = (a + b) / 2
        # Stampo il punto c nel grafico
        plt.plot(c, f(c), 'og')
        if abs(f(c)) < epsilon:
            print(f"Convergenza raggiunta dopo {i+1} iterazioni.")
            print(f"Lo zero calcolato è {c}")
            cn = False
            cond = False
            plt.plot(c, f(c), 'or', label='Convergenza')

        if cond and f(a) * f(c) < 0:
            b = c
        elif cond:
            a = c
        if cond:
            fk[i] = abs(f(c))
        i = i + 1 


    if cn and i == max_iter:
        print("Numero massimo di iterazioni raggiunto senza convergenza.")
        print(f"Lo zero calcolato è {c}")
    
    plt.grid()
    plt.legend()
    
    return c, i, fk[:i+1]

def metodo_punto_fisso(g, x0, max_iter, epsilon1, epsilon2, alfa, beta):

    # Stampa metodo punto fisso
    x = np.linspace(alfa, beta, 400)
    plt.subplot(1, 3, 2)
    plt.title ("Metodo delle Iterazioni di Punto Fisso")
    y = np.zeros_like(x)
    plt.plot(x, y, 'yellow', label='y = 0')
    plt.plot (x, x, 'green', label='y = x')
    plt.plot (x, f(x), 'blue', label='y = f(x)')
    plt.plot (x, g(x), 'orange', label='y = g(x)')

    # Metodo delle iterazioni di punto fisso
    print("\nMetodo delle Iterazioni di Punto Fisso:")
    i = 0
    cond = True
    xk = x0
    fk = np.zeros(max_iter)
    fk[0] = abs(f(x0))
    while cond and i < max_iter:
        x = g(xk)
        plt.plot ([xk, xk], [xk, g(xk)], 'r-')
        plt.plot ([xk, g(xk)], [g(xk), g(xk)], 'r-')


        if abs(f(x)) < epsilon2:
            print(f"Convergenza raggiunta dopo {i+1} iterazioni")
            print(f"Lo zero calcolato è {x}")
            # linea verticale al punto di convergenza
            plt.axvline(x=x, color='red', linestyle='--')
            # Segnalo la convergenza nel grafico
            plt.plot(x, f(x), 'ro', label='Convergenza')
            cond = False
        if cond and abs(x - xk) < epsilon1:
            print(f"Convergenza raggiunta dopo {i} iterazioni")
            print(f"Lo zero calcolato è {x}")
            # linea verticale al punto di convergenza
            plt.axvline(x=x, color='red', linestyle='--')  
            plt.plot(x, f(x), 'ro', label='Convergenza')      
            cond = False
        if cond:
            fk[i+1] = abs(f(x))
        xk = x
        i = i + 1

    if cond and i == max_iter:
        print("Numero massimo di iterazioni raggiunto senza convergenza.")
        print(f"Ultimo valore calcolato è {xk}")

    d = 2
    plt.xlim(-d, d)  # mostra solo l'intervallo [-10, 10] sull'asse x
    plt.ylim(-d, d)   # mostra solo l'intervallo [-10, 10] sull'asse y
    plt.grid()
    plt.legend()




    return xk, i, fk[:i+1]


def metodo_newton(f, df, x0, max_iter, epsilon1, epsilon2, alfa, beta):

    # Stampa metodo di Newton
    x = np.linspace(alfa, beta, 400)
    plt.subplot(1, 3, 3)
    plt.title ("Metodo di Newton")
    plt.plot(x0, 0, 'ro', color='pink', label='Punto iniziale')
    y = np.zeros_like(x)
    plt.plot(x, y, 'yellow', label='y = 0')
    #plt.plot (x, x, 'g', label='y = x')
    plt.plot (x, f(x), 'blue', label='y = f(x)')
    # Metodo di Newton
    print("\nMetodo di Newton:")
    i = 0
    cond = True
    xk = x0
    f_xk = np.zeros(max_iter)
    f_xk[0] = abs(f(xk))
    if abs(df(xk)) < 1e-10:
        print("La derivata è zero. Il metodo di Newton non può essere applicato.")
        plt.legend()
        plt.grid()
        plt.show()
        return None, 0, []
    while cond and i < max_iter:
        df_xk = df(xk)
        # Segnalo il punto tangente nel grafico
        plt.plot(xk, f(xk), 'yo') 
        # Tangent line at (xk, f(xk))
        tangente = df_xk * (x - xk) + f(xk)
        # linea tangente tratteggiata
        plt.plot(x, tangente, 'b', linestyle='--')
        xk1 = xk - f(xk) / df(xk)
        f_xk[i+1] = abs(f(xk1))
        if abs(xk1 - xk) < epsilon1:
            print(f"Convergenza raggiunta dopo {i+1} iterazioni.")
            print(f"Lo zero calcolato è {xk1}")
            plt.plot(xk1, f(xk1), 'ro', label='Convergenza')
            cond = False

        if abs(f(xk1)) < epsilon2:
            print(f"Convergenza raggiunta dopo {i+1} iterazioni")
            print(f"Lo zero calcolato è {xk1}")
            plt.plot(xk1, f(xk1), 'ro', label='Convergenza')
            cond = False

        i = i + 1
        xk = xk1

    d = 2
    plt.xlim(-d, d)  # mostra solo l'intervallo [-10, 10] sull'asse x
    plt.ylim(-d, d)   # mostra solo l'intervallo [-10, 10] sull'asse y
    plt.grid()
    plt.show()

    
    return xk, i, f_xk[:i+1]


def homework1(f, df, x0, max_iter, epsilon, alfa, beta, epsilon1, epsilon2, a, b):
    sol1, n_iter1, fk1 = metodo_bisezione(f, a, b, max_iter, epsilon)
    sol2, n_iter2, fk2 = metodo_punto_fisso(g, x0, max_iter, epsilon1, epsilon2, alfa, beta)
    sol3, n_iter3, fk3 = metodo_newton(f, df, x0, max_iter, epsilon1, epsilon2, alfa, beta)
    return sol1, sol2, sol3, n_iter1, n_iter2, n_iter3, fk1, fk2, fk3

sol1, sol2, sol3, n_iter1, n_iter2, n_iter3, fk1, fk2, fk3 = homework1(f, df, x0, max_iter, epsilon, alfa, beta, epsilon1, epsilon2, a, b)

plt.figure(figsize=(12, 4))
plt.subplot(1, 3, 1)
plt.title ("Bisezione")
fk = fk1[:n_iter1+1] # Truncate fk to the number of iterations performed
plt.plot(range(n_iter1+1), fk, 'm', label='Valori f(c) ad ogni iterazione')
plt.legend()
plt.grid()



plt.subplot(1, 3, 2)
plt.title ("Punto Fisso")
fk = fk2[:n_iter2+1] # Truncate fk to the number of iterations performed
plt.plot(range(n_iter2+1), fk, 'm', label='Valori f(c) ad ogni iterazione')
plt.legend()
plt.grid()

if (n_iter3 > 0): n_iter3 += 1
plt.subplot(1, 3, 3)
plt.title ("Newton")
fk = fk3[:n_iter3] # Truncate fk to the number of iterations performed
plt.plot(range(n_iter3), fk, 'm', label='Valori f(c) ad ogni iterazione')
plt.legend()
plt.grid()
plt.tight_layout()
plt.show()
n_iter3 -= 1


# Dati di esempio (i tuoi risultati)
risultati = np.array([
    [sol1, n_iter1,  None],
    [sol2, n_iter2,  x0],
    [sol3, n_iter3,  x0]
])

intestazioni = ["Soluzione", "Iterazioni", "Punto iniziale"]

# --- Creazione figura ---
fig, ax = plt.subplots()

# Nasconde assi
ax.axis('tight')
ax.axis('off')

# Crea la tabella
tabella = ax.table(
    cellText=risultati,
    colLabels=intestazioni,
    loc='center',
    cellLoc='center'
)

# Migliora la leggibilità
tabella.auto_set_font_size(False)
tabella.set_fontsize(12)
tabella.scale(1.2, 1.2)

plt.show()