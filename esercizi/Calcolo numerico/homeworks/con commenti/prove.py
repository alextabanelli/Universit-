import numpy as np
import matplotlib.pyplot as plt
from skimage import io, color
from skimage.util import img_as_float

# Importazione moduli
try:
    from ProblemiInversi import operators, solvers, utilities
except ImportError:
    import operators, solvers, utilities

# =============================================================================
# 1. PREPARAZIONE DATI
# =============================================================================

# Caricamento Immagine
filename = 'hulk.bmp'
try:
    image_source = io.imread(filename)
    if image_source.ndim == 3:
        x_true = color.rgb2gray(image_source)
    else:
        x_true = image_source
    if x_true.max() > 1.0:
        x_true = x_true / 255.0
except FileNotFoundError:
    print(f"Errore: File {filename} non trovato. Uso immagine dummy.")
    x_true = np.zeros((100, 100)); x_true[20:80, 20:80] = 1.0 

m, n = x_true.shape
print(f"Immagine dimensioni: {m}x{n}")

# Creazione Operatore Blur
sigma = 2.0
k_size = 15
kernel = utilities.gaussian2d_kernel(k_size, sigma)
A = operators.ConvolutionOperator(kernel)

# Creazione Dati Rumorosi
noise_level = 0.1 # 10% di rumore
b_clean = A(x_true)
b_noisy = utilities.gaussian_noise(b_clean, noise_level)

print(f"Problema creato con Noise Level: {noise_level*100}%")

# =============================================================================
# 2. CODICE CGLS (NAIVE)
# =============================================================================
print("Avvio ricostruzione Naive CGLS...")

# Inizializzazione Solver
# Senza passare L e lambda, CGLS risolve il problema ai minimi quadrati standard: min ||Ax - y||^2
cgls_solver = solvers.CGLS(A)

# Parametri
kmax = 50   # Numero di iterazioni (Attenzione alla semiconvergenza!)
x0 = np.zeros_like(b_noisy) # Partenza da zero

# Soluzione
# Nota: La classe CGLS in solvers.py restituisce solo la soluzione x
x_cgls = cgls_solver.solve(b_noisy, x0, kmax=kmax)

# Calcolo errore
err_cgls = utilities.rel_err(x_cgls, x_true)
print(f"Ricostruzione completata. Errore Relativo: {err_cgls:.4f}")

# =============================================================================
# 3. VISUALIZZAZIONE
# =============================================================================
plt.figure(figsize=(15, 6))

# Ground Truth
plt.subplot(1, 3, 1)
plt.imshow(x_true, cmap='gray')
plt.title("Ground Truth")
plt.axis('off')

# Dati Rumorosi
plt.subplot(1, 3, 2)
plt.imshow(b_noisy, cmap='gray')
plt.title(f"Input Rumoroso\nNoise {noise_level*100}%")
plt.axis('off')

# Risultato CGLS
plt.subplot(1, 3, 3)
plt.imshow(x_cgls, cmap='gray')
plt.title(f"Naive CGLS\nIterazioni: {kmax}\nErr: {err_cgls:.4f}")
plt.axis('off')

plt.tight_layout()
plt.show()