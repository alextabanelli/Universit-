import numpy as np
import matplotlib.pyplot as plt


# Funzione da analizzare
f = lambda x: x**2 - np.cos(x)
df = lambda x: 2*x + np.sin(x)
g = lambda x: np.sqrt(np.cos(x)) #if np.cos(x) >= 0 else np.nan

a = -20
b = 20





# Parametri comuni
max_iter = 20
# Epsilon
epsilon = 1e-6
epsilon1 = 1e-6
epsilon2 = 1e-6
# Punto iniziale
x0 = 15


# Stampa metodo di Newton
x = np.linspace(a, b, 400)
plt.figure(figsize=(8, 8))
plt.title ("Metodo di Newton")
plt.plot(x0, 0, 'ro', color='pink', label='Punto iniziale')
y = np.zeros_like(x)
plt.plot(x, y, 'b', label='y = 0')
#plt.plot (x, x, 'g', label='y = x')
plt.plot (x, f(x), 'r', label='y = f(x)')



# Metodo di Newton
def newton(f, df, x0, max_iter, epsilon):
    print("\nMetodo di Newton:")
    xk = x0
    if abs(df(xk)) < 1e-10:
        print("La derivata è zero. Il metodo di Newton non può essere applicato.")
        return None, 0
    for i in range(max_iter):
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
            break
        xk = xk1
    return xk, i


d = 20


sol, n_iter = newton(f, df, x0, max_iter, epsilon)

plt.xlim(-d, d)  # mostra solo l'intervallo [-10, 10] sull'asse x
plt.ylim(-100, f(b)+10)   # mostra solo l'intervallo [-10, 10] sull'asse y
#Legenda
#plt.gca().set_aspect(0.5)  # scala logaritmica per l’asse Y
#plt.autoscale(enable=True, axis='y', tight=True)

plt.legend()
plt.grid()
plt.show() 