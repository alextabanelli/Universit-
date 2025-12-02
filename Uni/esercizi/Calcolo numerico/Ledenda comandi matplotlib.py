Ledenda comandi matplotlib

Punto:
P(x, y)
plt.plot(x, y, 'ro')

Linea:
Linea (x1, y1) a (x2, y2)
plt.plot([x1, x2], [y1, y2], 'r-')


Zoom:
plt.xlim(-2, 2)  # mostra solo l'intervallo [-2, 2] sull'asse x
plt.ylim(0, 4)   # mostra solo l'intervallo [0, 4] sull'asse y

Legenda:
plt.legend()
Nella legenda vengono mostrati tutti gli elementi a cui è stato associato un label.
