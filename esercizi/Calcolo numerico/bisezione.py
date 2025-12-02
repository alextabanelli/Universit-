import numpy as np
import matplotlib.pyplot as plt


# Funzione da analizzare
f = lambda x: x**2 - np.cos(x)
df = lambda x: 2*x + np.sin(x)
g = lambda x: np.sqrt(np.cos(x)) #if np.cos(x) >= 0 else np.nan

a = -100
b = 100

# Stampa funzione 
x = np.linspace(a, b, 400)
plt.figure(figsize=(8, 8))
plt.title ("Funzione f(x) = x^2 - cos(x)")
plt.plot (x, f(x), 'r', label='f(x)')
plt.plot (x, g(x), 'g', label='g(x)')
y = np.zeros_like(x)
plt.plot(x, y, 'b', label='y = 0 (zeros_like)')
plt.grid()
plt.legend()
plt.show()


# Parametri comuni
max_iter = 20
# Epsilon
epsilon = 1e-6
epsilon1 = 1e-6
epsilon2 = 1e-6
# Punto iniziale
x0 = 0
# Intervallo
a = 0
b = 6


# Stampa metodo di bisezione
x = np.linspace(a, b)
plt.figure(figsize=(8, 8))
plt.title ("Metodo di Bisezione")
plt.plot (x, f(x), 'r')
y = np.zeros_like(x)
plt.plot(x, y, 'b', label='y = 0 (zeros_like)')
plt.xlim(a, b)  # mostra solo l'intervallo [0, 6] sull'asse x
plt.ylim(f(a), f(b))   # mostra solo l'intervallo [f(0), f(6)] sull'asse y


# Metodo di bisezione
def bisezione (f, a, b, max_iter, epsilon):
    cn = True
    print("\nMetodo di Bisezione:")
    print(f"a = {a}, b = {b}")
    if f(a) * f(b) >= 0.0:
        print("Il metodo di bisezione non può essere applicato.")
        return None, 0
    for i in range(max_iter):
        c = (a + b) / 2
        # Stampo il punto c nel grafico
        plt.plot(c, f(c), 'or')
        if abs(f(c)) < epsilon:
            print(f"Convergenza raggiunta dopo {i} iterazioni.")
            print(f"Lo zero calcolato è {c}")
            cn = False
            break
        if f(a) * f(c) < 0:
            b = c
        else:
            a = c

    if cn and i == max_iter - 1:
        print("Numero massimo di iterazioni raggiunto senza convergenza.")
        print(f"Lo zero calcolato è {c}")
    
    return c, i


sol, n_iter = bisezione(f, a, b, max_iter, epsilon)


plt.grid()
plt.show()


