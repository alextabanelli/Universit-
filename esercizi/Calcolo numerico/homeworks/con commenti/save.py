import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import scipy as sp
import scipy.linalg  # Importato come nel notebook di riferimento per l'algebra lineare

# ==============================================================================
# 1. FUNZIONI MATEMATICHE E RISOLUTORI
# ==============================================================================

def build_vandermonde(x, d):
    """
    Costruisce la matrice di Vandermonde.
    Usa np.vander come suggerito nel testo dell'homework.
    increasing=True genera potenze crescenti: [1, x, x^2, ...]
    """
    return np.vander(x, N=d + 1, increasing=True)

def solve_ls_svd(X, y):
    """
    Risolve il problema ai minimi quadrati min ||X*alpha - y||_2^2
    utilizzando la fattorizzazione SVD di Scipy (come da notebook sistemi_lineari).
    """
    # 1. SVD: X = U * S * Vt
    # scipy.linalg.svd è spesso più efficiente di numpy.linalg.svd
    U, s, Vt = sp.linalg.svd(X, full_matrices=False)
    
    # 2. Inversione dei valori singolari (1/s_i)
    # Gestione valori vicini a zero per stabilità numerica
    threshold = 1e-12
    s_inv = np.zeros_like(s)
    mask = s > threshold
    s_inv[mask] = 1.0 / s[mask]
    
    # 3. Calcolo della soluzione: alpha = V * S_inv * U.T * y
    # Nota: Vt restituito da scipy è già trasposto (V^T)
    # U.T @ y -> Proiezione di y su U
    uty = U.T @ y
    # s_inv * ... -> Scaling per l'inversa dei valori singolari
    s_uty = s_inv * uty
    # Vt.T @ ... -> Proiezione nello spazio dei coefficienti (Vt.T = V)
    alpha = Vt.T @ s_uty
    
    return alpha

def poly_eval(x, alpha):
    """Calcola i valori del polinomio dati i coefficienti alpha."""
    d = len(alpha) - 1
    X = build_vandermonde(x, d)
    return X @ alpha

# ==============================================================================
# 2. GESTIONE DATI E TEST
# ==============================================================================

def generate_synthetic_data(n, d, sigma=0.1, alpha=None):
    """Genera il problema test sintetico."""
    if alpha is None:
        alpha = np.random.randn(d + 1)
        
    x = np.linspace(0, 1, n)
    
    # Calcolo y vera
    y_true = poly_eval(x, alpha)
    
    # Aggiunta rumore
    e = np.random.normal(loc=0, scale=sigma, size=n)
    y_noisy = y_true + e
    
    return x, y_noisy, alpha, y_true

def load_and_normalize_csv(csv_path):
    """Carica e normalizza i dati dal CSV (necessario per stabilità SVD)."""
    df = pd.read_csv(csv_path)
    
    # Estrazione colonne (assumiamo col 0 = X, col 1 = Y)
    x_raw = df.iloc[:, 0].values.astype(float)
    y_raw = df.iloc[:, 1].values.astype(float)
    
    # Ordinamento per plotting corretto
    sort_idx = np.argsort(x_raw)
    x_sorted = x_raw[sort_idx]
    y_sorted = y_raw[sort_idx]
    
    # Normalizzazione x in [0, 1]
    x_min, x_max = np.min(x_sorted), np.max(x_sorted)
    x_norm = (x_sorted - x_min) / (x_max - x_min)
    
    return x_norm, y_sorted, x_raw

# ==============================================================================
# 3. TEST SISTEMI LINEARI E FATTORIZZAZIONE LU
# ==============================================================================

def run_linear_systems_tests():
    """Esegue i test su sistemi lineari e fattorizzazione LU."""
    print("\n--- TEST SISTEMI LINEARI E FATTORIZZAZIONE LU ---")

    # Problema Test 1: Fattorizzazione LU semplice
    print("\n[Problema Test 1] Fattorizzazione LU")
    B = np.array([[9, 3, 6], [3, 4, 6], [0, 8, 8]])
    
    # La funzione scipy.linalg.lu restituisce le tre matrici L, U, P tali che: B = P @ L @ U
    P, L, U = sp.linalg.lu(B)
    
    # Calcolo errore fattorizzazione
    err = np.linalg.norm(B - P @ L @ U)
    print(f'Norma errore LU: {err:.4e}')

    # Problema Test 2: Risoluzione sistema lineare con LU factor
    print("\n[Problema Test 2] Risoluzione Sistema Lineare")
    A = np.array([[3, -7, 2, 2], [-3, 5, 1, 0], [6, -4, 0, -5], [-9, 5, -5, 12]])
    b = np.array([-9, 5, 7, 11])

    # scipy.linalg.lu_factor restituisce (lu, piv) dove lu contiene L e U compattate
    lu, piv = sp.linalg.lu_factor(A)
    print('Matrice LU fattorizzata (compatta):\n', lu)

    # Risoluzione usando lu_solve
    x = sp.linalg.lu_solve((lu, piv), b)
    print('Soluzione con lu_solve:', x)
    
    # Verifica residuo
    res_norm = np.linalg.norm(b - A @ x)
    print(f'Norma del residuo (lu_solve): {res_norm:.4e}')

    # Risoluzione diretta con numpy.linalg.solve (usa LU internamente)
    xx = np.linalg.solve(A, b)
    print('Soluzione con np.linalg.solve:', xx)
    
    # Verifica residuo
    res_norm_np = np.linalg.norm(b - A @ xx)
    print(f'Norma del residuo (np.linalg.solve): {res_norm_np:.4e}')


# ==============================================================================
# 4. FUNZIONI DI ESECUZIONE (Main)
# ==============================================================================

def run_synthetic_tests():
    """Esegue i test su dati sintetici (Underfit, Fit Corretto, Overfit)."""
    print("\n--- TEST DATI SINTETICI (REGRESSIONE) ---")
    
    # Scenari: (n_punti, grado_modello, titolo, alpha_fisso_opzionale)
    scenarios = [
        (50, 3, "Fit Corretto (d=3)", np.array([0.5, -1.2, 2.5, 1.0])),
        (40, 1, "Underfit (d=1, Reale=3)", None),
        (15, 12, "Overfit (d=12, Reale=3)", None)
    ]
    
    plt.figure(figsize=(15, 4))
    
    # Alpha reale condiviso per underfit/overfit per confronto coerente
    shared_alpha = np.random.randn(4) 
    
    for i, (n, d_approx, title, alpha_fixed) in enumerate(scenarios):
        # Usa alpha fisso se fornito, altrimenti quello condiviso (se il grado reale è 3)
        alpha_real = alpha_fixed if alpha_fixed is not None else shared_alpha
        
        # Generazione
        x, y, _, y_true_curve = generate_synthetic_data(n, 3, alpha=alpha_real)
        
        # Risoluzione
        X_mat = build_vandermonde(x, d_approx)
        alpha_est = solve_ls_svd(X_mat, y)
        y_pred = poly_eval(x, alpha_est)
        
        # Calcolo Errori
        residual_norm = sp.linalg.norm(y - y_pred) # Norma del residuo (stile notebook)
        mse = np.mean((y - y_pred)**2)
        
        # Plot
        plt.subplot(1, 3, i + 1)
        plt.scatter(x, y, color='red', s=15, label='Dati', alpha=0.6)
        plt.plot(x, y_true_curve, 'b--', label='Vera', alpha=0.4)
        plt.plot(x, y_pred, 'g-', label=f'Fit d={d_approx}')
        plt.title(f"{title}\nResiduo: {residual_norm:.2f} | MSE: {mse:.2e}")
        plt.legend()
        plt.grid(True, alpha=0.3)
        
        print(f"Scenario '{title}': Norma Residuo = {residual_norm:.4f}")

    plt.tight_layout()
    plt.show()

def run_kaggle_test(csv_path, degrees):
    """Esegue la regressione polinomiale sul dataset CSV."""
    print(f"\n--- TEST DATASET KAGGLE: {csv_path} ---")
    
    x, y, _ = load_and_normalize_csv(csv_path)
    
    plt.figure(figsize=(10, 6))
    plt.scatter(x, y, color='gray', s=10, alpha=0.3, label='Dati CSV')
    
    colors = plt.cm.viridis(np.linspace(0, 1, len(degrees)))
    
    for i, d in enumerate(degrees):
        # Risoluzione
        X_mat = build_vandermonde(x, d)
        alpha = solve_ls_svd(X_mat, y)
        y_pred = poly_eval(x, alpha)
        
        # Metriche
        residual_norm = sp.linalg.norm(y - y_pred)
        mse = np.mean((y - y_pred)**2)
        
        print(f"Grado d={d:3d} | Norma Residuo: {residual_norm:.2e} | MSE: {mse:.2e}")
        
        plt.plot(x, y_pred, color=colors[i], linewidth=2, label=f'd={d}')
        
    plt.title(f"Regressione Polinomiale (SVD) su {csv_path}")
    plt.xlabel("X (Normalizzata)")
    plt.ylabel("Y")
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.show()

# ==============================================================================
# ESECUZIONE
# ==============================================================================

if __name__ == "__main__":
    # 1. Test Sistemi Lineari e LU (Nuova Sezione)
    run_linear_systems_tests()

    # 2. Test Sintetici Regressione
    run_synthetic_tests()

    # 3. Test File CSV (Opzionale, decommentare se il file è presente)
    file_csv = "submission.csv"
    run_kaggle_test(file_csv, degrees=[1, 3, 5, 15])