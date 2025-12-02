import numpy as np
import matplotlib.pyplot as plt

# Creiamo due vettori di esempio
a = 0
b = 2*np.pi
N = 50

x = np.linspace(a, b, N)
y = np.sin(x)

# Visualizzazione
plt.plot(x, y)
plt.show()