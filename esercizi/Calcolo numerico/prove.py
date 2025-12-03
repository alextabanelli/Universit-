import numpy as np
import matplotlib.pyplot as plt

# ==========================
#  Dati base della superficie
# ==========================
x = np.linspace(-2, 2, 50)
y = np.linspace(-2, 2, 50)
X, Y = np.meshgrid(x, y)
Z = X**2 + Y**2

# Punto da evidenziare
xp, yp = 1, 1
zp = xp**2 + yp**2

fig = plt.figure(figsize=(14, 5))

# =============================================================
# 1️⃣ depthshade=False — punto visibile sopra la superficie
# =============================================================
ax1 = fig.add_subplot(1, 4, 1, projection='3d')
ax1.set_title("1️⃣ depthshade=False")
ax1.plot_surface(X, Y, Z, cmap='plasma')
ax1.scatter(xp, yp, zp, color='red', s=80, edgecolor='k', depthshade=False)
ax1.view_init(elev=25, azim=45)

# =============================================================
# 2️⃣ zorder alto + depthshade=False
# =============================================================
ax2 = fig.add_subplot(1, 4, 2, projection='3d')
ax2.set_title("2️⃣ zorder alto + depthshade=False")
ax2.plot_surface(X, Y, Z, cmap='plasma', zorder=1)
ax2.scatter(xp, yp, zp, color='lime', s=90, edgecolor='k',
            zorder=10, depthshade=False)
ax2.view_init(elev=25, azim=45)

# =============================================================
# 3️⃣ ax.plot con marker 3D (funziona sempre)
# =============================================================
ax3 = fig.add_subplot(1, 4, 3, projection='3d')
ax3.set_title("3️⃣ ax.plot con marker 3D")
ax3.plot_surface(X, Y, Z, cmap='plasma')
ax3.plot([xp], [yp], [zp], marker='o', color='orange',
         markersize=8, markeredgecolor='k', zorder=10)
ax3.view_init(elev=25, azim=45)

# =============================================================

# =============================================================
# 4️⃣ ax.plot con marker 3D (funziona sempre)
# =============================================================
ax4 = fig.add_subplot(1, 4, 4, projection='3d')
ax4.set_title("4️⃣ ax.plot con marker 3D")
ax4.plot_surface(X, Y, Z, cmap='plasma')
ax4.plot3D([xp], [yp], [zp], marker='o', color='orange',
         markersize=8, markeredgecolor='k', zorder=10)
ax4.view_init(elev=25, azim=45)

# =============================================================


plt.tight_layout()
plt.show()
