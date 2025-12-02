import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# 1️⃣ Definizione della funzione
def f(x, y):
    return x**2 + y**2

# 2️⃣ Creazione griglia di punti
x = np.linspace(-5, 5, 100)
y = np.linspace(-5, 5, 100)
X, Y = np.meshgrid(x, y)
Z = f(X, Y)

# 3️⃣ Creazione della figura
fig = plt.figure(figsize=(12, 5))

# 🔹 Subplot 1 — Curve di livello 2D
ax1 = fig.add_subplot(1, 2, 2)  # subplot diviso in 1 riga, 2 colonne, 2° subplot
contours = ax1.contour(X, Y, Z, levels=30, cmap='coolwarm')
ax1.clabel(contours, inline=True, fontsize=8)
ax1.set_title("Curve di livello di f(x, y) = x² + y²")
ax1.set_xlabel("x")
ax1.set_ylabel("y")
ax1.axis("equal")

# 🔹 Subplot 2 — Superficie 3D
ax2 = fig.add_subplot(1, 2, 1, projection='3d') # subplot diviso in 1 riga, 2 colonne, 1° subplot
surf = ax2.plot_surface(X, Y, Z, cmap='plasma', edgecolor='none')  # plotsurface crea la superficie 3D (X, Y, Z)
ax2.set_title("Superficie 3D di f(x, y) = x² + y²")
ax2.set_xlabel("x")
ax2.set_ylabel("y")
ax2.set_zlabel("f(x, y)")
fig.colorbar(surf, ax=ax2, shrink=0.5, aspect=10, label='f(x, y)')

# 4️⃣ Mostra tutto insieme
plt.tight_layout() # tight_layout serve per evitare sovrapposizioni tra i subplot
plt.show()
