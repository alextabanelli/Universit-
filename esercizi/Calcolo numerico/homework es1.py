import numpy as np
import matplotlib.pyplot as plt


# Funzione da analizzare
# e^x − 3x
f = lambda x: np.exp(x) - 3*x
df = lambda x: np.exp(x) - 3
g = lambda x: np.exp(x)/3

alfa = -10
beta = 10





# Parametri comuni
max_iter = 100
# Epsilon
epsilon = 1e-6
epsilon1 = 1e-6
epsilon2 = 1e-6
# Punto iniziale
x0 = 0
# Intervallo
a = -6
b = 1



def metodo_bisezione(f, a, b, max_iter, epsilon):
    # Stampa metodo di bisezione
    x = np.linspace(a, b)
    plt.figure(figsize=(8, 8))
    plt.title ("Metodo di Bisezione")
    plt.plot (x, f(x), 'r')
    y = np.zeros_like(x)
    plt.plot(x, y, 'b', label='y = 0')
    plt.xlim(a, b)  # mostra solo l'intervallo [-6, 1] sull'asse x
    plt.ylim(f(a), f(b))   # mostra solo l'intervallo [f(-6), f(1)] sull'asse y
    # Metodo di bisezione
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
        plt.plot(c, f(c), 'or')
        if abs(f(c)) < epsilon:
            print(f"Convergenza raggiunta dopo {i} iterazioni.")
            print(f"Lo zero calcolato è {c}")
            cn = False
            cond = False
        if cond and f(a) * f(c) < 0:
            b = c
        elif cond:
            a = c
        if cond:
            i = i + 1 

    if cn and i == max_iter:
        print("Numero massimo di iterazioni raggiunto senza convergenza.")
        print(f"Lo zero calcolato è {c}")
    
    plt.grid()
    plt.show()

    return c, i

def metodo_punto_fisso(g, x0, max_iter, epsilon1, epsilon2, alfa, beta):

    # Stampa metodo punto fisso
    x = np.linspace(alfa, beta, 400)
    plt.figure(figsize=(8, 8))
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

    while cond and i < max_iter:
        x = g(xk)
        plt.plot ([xk, xk], [xk, g(xk)], 'r-')
        plt.plot ([xk, g(xk)], [g(xk), g(xk)], 'r-')


        if abs(f(x)) < epsilon2:
            print(f"Convergenza raggiunta dopo {i} iterazioni")
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
    plt.show()
    return xk, i


def metodo_newton(f, df, x0, max_iter, epsilon, alfa, beta):

    # Stampa metodo di Newton
    x = np.linspace(alfa, beta, 400)
    plt.figure(figsize=(8, 8))
    plt.title ("Metodo di Newton")
    plt.plot(x0, 0, 'ro', color='pink', label='Punto iniziale')
    y = np.zeros_like(x)
    plt.plot(x, y, 'b', label='y = 0')
    #plt.plot (x, x, 'g', label='y = x')
    plt.plot (x, f(x), 'r', label='y = f(x)')
    # Metodo di Newton
    print("\nMetodo di Newton:")
    i = 0
    cond = True
    xk = x0
    if abs(df(xk)) < 1e-10:
        print("La derivata è zero. Il metodo di Newton non può essere applicato.")
        return None, 0
    while cond and i < max_iter:
        df_xk = df(xk)
        f_xk = f(xk)
        # Segnalo il punto tangente nel grafico
        plt.plot(xk, f_xk, 'yo', label='Punto di tangenza' if i == 0 else "")
        # Tangent line at (xk, f(xk))
        tangente = df_xk * (x - xk) + f_xk
        # linea tangente tratteggiata
        plt.plot(x, tangente, 'b', linestyle='--', label='Tangente' if i == 0 else "")
        xk1 = xk - f(xk) / df(xk)
        plt.plot ([xk1, xk1], [0, f(xk1)], 'g',  label='Individo il punto successivo' if i == 0 else "")
        if abs(xk1 - xk) < epsilon:
            print(f"Convergenza raggiunta dopo {i} iterazioni.")
            print(f"Lo zero calcolato è {xk1}")
            plt.plot(xk1, f(xk1), 'ro', label='Convergenza')
            cond = False
        i = i + 1
        if cond: xk = xk1
    d = 20
    plt.xlim(-d, d)  # mostra solo l'intervallo [-10, 10] sull'asse x
    plt.ylim(-100, f(b)+10)   # mostra solo l'intervallo [-10, 10] sull'asse y
    #Legenda
    #plt.gca().set_aspect(0.5)  # scala logaritmica per l’asse Y
    #plt.autoscale(enable=True, axis='y', tight=True)
    plt.legend()
    plt.grid()
    plt.show()
    return xk, i


def homework1(f, df, x0, max_iter, epsilon, alfa, beta, epsilon1, epsilon2, a, b):
    sol, n_iter = metodo_bisezione(f, a, b, max_iter, epsilon)
    sol, n_iter = metodo_punto_fisso(g, x0, max_iter, epsilon1, epsilon2, alfa, beta)
    sol, n_iter = metodo_newton(f, df, x0, max_iter, epsilon, alfa, beta)
    return sol, n_iter

homework1(f, df, x0, max_iter, epsilon, alfa, beta, epsilon1, epsilon2, a, b)

