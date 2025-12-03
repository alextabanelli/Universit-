import numpy as np
import matplotlib.pyplot as plt


# Funzione da analizzare
f = lambda x: np.exp(x) - 3*x
df = lambda x: np.exp(x) - 3
g = lambda x: np.exp(x)/3

a = -10
b = 10





# Parametri comuni
max_iter = 20
# Epsilon
epsilon = 1e-6
epsilon1 = 1e-6
epsilon2 = 1e-6
# Punto iniziale
x0 = 1



# Stampa metodo punto fisso
x = np.linspace(a, b, 400)
plt.figure(figsize=(8, 8))
plt.title ("Metodo delle Iterazioni di Punto Fisso")
y = np.zeros_like(x)
plt.plot(x, y, 'yellow', label='y = 0')
plt.plot (x, x, 'green', label='y = x')
plt.plot (x, f(x), 'blue', label='y = f(x)')
plt.plot (x, g(x), 'orange', label='y = g(x)')


# Metodo delle iterazioni di punto fisso
def punto_fisso(g, x0, max_iter, epsilon1, epsilon2):
    print("\nMetodo delle Iterazioni di Punto Fisso:")
    xk = x0

    for i in range(max_iter):
        x = g(xk)
        plt.plot ([xk, xk], [xk, g(xk)], 'r-')
        plt.plot ([xk, g(xk)], [g(xk), g(xk)], 'r-')


        if abs(f(x)) < epsilon2:
            print(f"Convergenza raggiunta dopo {i} iterazioni.1")
            print(f"Lo zero calcolato è {x}")
            # linea verticale al punto di convergenza
            plt.axvline(x=x, color='red', linestyle='--')
            # Segnalo la convergenza nel grafico
            plt.plot(x, f(x), 'ro', label='Convergenza')
            break
        if abs(x - xk) < epsilon1:
            print(f"Convergenza raggiunta dopo {i} iterazioni.2")
            print(f"Lo zero calcolato è {x}")
            # linea verticale al punto di convergenza
            plt.axvline(x=x, color='red', linestyle='--')  
            plt.plot(x, f(x), 'ro', label='Convergenza')      
            break
        xk = x

    if i == max_iter - 1:
        print("Numero massimo di iterazioni raggiunto senza convergenza.")
        print(f"Ultimo valore calcolato è {xk}")
    return xk, i


sol, n_iter = punto_fisso(g, x0, max_iter, epsilon1, epsilon2)

d = 2

plt.xlim(-d, d)  # mostra solo l'intervallo [0, 6] sull'asse x
plt.ylim(-d, d)   # mostra solo l'intervallo [f(0), f(6)] sull'asse y
#Legenda
plt.legend()
plt.grid()
plt.show()
