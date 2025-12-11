import numpy as np
import matplotlib.pyplot as plt


# Funzione da analizzare
# e^x − 3x
f = lambda x: x*x - np.cos(x)
df = lambda x: 2*x + np.sin(x)
g = lambda x: np.sqrt(np.cos(x))

alfa = -10
beta = 10





# Parametri comuni
max_iter = 100
# Epsilon
epsilon = 1e-6
epsilon1 = 1e-6
epsilon2 = 1e-6
# Punto iniziale
x0 = 2.5
# Intervallo
a = 0
b = 100



def metodo_bisezione(f, a, b, max_iter, epsilon):
    cond = True
    i = 0
    if f(a) * f(b) >= 0.0:
        return None, 0
    while cond and i < max_iter:
        c = (a + b) / 2
        if abs(f(c)) < epsilon:
            cond = False
        if cond and f(a) * f(c) < 0:
            b = c
        elif cond:
            a = c
        i = i + 1 
    return c, i

def metodo_punto_fisso(g, x0, max_iter, epsilon1, epsilon2):
    i = 0
    cond = True
    xk = x0
    while cond and i < max_iter:
        x = g(xk)
        if abs(x - xk) < epsilon1 or abs(f(x)) < epsilon2:
            cond = False
        xk = x
        i = i + 1
    return xk, i


def metodo_newton(f, df, x0, max_iter, epsilon1, epsilon2):
    i = 0
    cond = True
    xk = x0
    if abs(df(xk)) < 1e-10:
        return None, 0
    while cond and i < max_iter:
        xk1 = xk - f(xk) / df(xk)
        if abs(xk1 - xk) < epsilon1 or abs(f(xk1)) < epsilon2:
            cond = False
        xk = xk1
        i = i + 1
    return xk, i


def homework1(f, df, x0, max_iter, epsilon, epsilon1, epsilon2, a, b, g):
    sol1, n_iter1 = metodo_bisezione(f, a, b, max_iter, epsilon)
    sol2, n_iter2 = metodo_punto_fisso(g, x0, max_iter, epsilon1, epsilon2)
    sol3, n_iter3 = metodo_newton(f, df, x0, max_iter, epsilon1, epsilon2)
    
    return sol1, sol2, sol3, n_iter1, n_iter2, n_iter3

sol1, sol2, sol3, n_iter1, n_iter2, n_iter3 = homework1(f, df, x0, max_iter, epsilon, epsilon1, epsilon2, a, b, g)

print(f"Intervallo di ricerca: [{a}, {b}], punto iniziale: {x0}, tolleranze: 10^-6")
print(f"Metodo di bisezione: zero = {sol1}, iterazioni = {n_iter1}")
print(f"Metodo di punto fisso: zero = {sol2}, iterazioni = {n_iter2}")
print(f"Metodo di Newton: zero = {sol3}, iterazioni = {n_iter3}")   