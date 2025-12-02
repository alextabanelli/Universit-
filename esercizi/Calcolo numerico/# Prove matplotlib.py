# Prove matplotlib

import matplotlib.pyplot as plt
import numpy as np

plt.plot(2, 3, 'ro')  # punto (x=2, y=3) in rosso ('r'), 'o' = marker circolare
plt.show()



x = np.linspace(-5, 5, 200)  # 200 punti da -5 a 5
y = x**2

plt.plot(x, y, 'm', label='y = x²')  # 'm' = magenta
plt.legend()
plt.grid(True)
plt.show()


plt.xlim(-2, 2)  # mostra solo l'intervallo [-2, 2] sull'asse x
plt.ylim(0, 4)   # mostra solo l'intervallo [0, 4] sull'asse y

x = np.linspace(-5, 5, 200)  # 200 punti da -5 a 5
y = x**2

plt.plot(x, y, 'm', label='y = x²')  # 'm' = magenta
plt.legend()
plt.grid(True)
plt.show()

x = [0, 1, 2, 3]
y = [0, 2, 1, 3]

c = 5

# come disegnare una linea verticale in x = c
plt.plot([c, c], [min(y), max(y)], 'k-')  # linea verticale tratteggiata nera

plt.show()