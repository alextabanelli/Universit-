import numpy as np
from matplotlib import pyplot as plt
from numpy import cos
# calcolo del punto fisso della funzione x-cos(x) con g(x)=cos(x)

def f_1(x): return x - cos(x)
def g_1(x): return cos(x)
 
f = f_1
g = g_1
a = -1
b = 1
x = np.linspace(a, b)
plt.figure(figsize=(12,6))
plt.title('$y = f(x) = x - cos(x)$ and $y=0$')
plt.plot(x, f(x))
plt.plot([a, b], [0, 0])
plt.grid(True)
plt.figure(figsize=(12,6))
plt.title('$y = g(x) = cos (x)$ and $y=x$')
plt.plot(x, g(x))
plt.plot(x, x)
plt.grid(True)
plt.show()
