{
 "cells": [
  {
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    "# Calcolo Numerico 2025-26 - Homework 2\n",
    "## Metodo del Gradiente e Gradiente Stocastico\n",
    "\n",
    "Questo notebook implementa il metodo di discesa del gradiente (GD) per funzioni in più variabili $f: \\mathbb{R}^n \\rightarrow \\mathbb{R}$[cite: 3, 4]. \n",
    "\n",
    "### Obiettivi:\n",
    "1. Estendere il GD a più variabili con passo fisso e backtracking.\n",
    "2. Implementare criteri di arresto specifici: \n",
    "   * Tolleranza gradiente: $10^{-6}$[cite: 6].\n",
    "   * Tolleranza differenza iterati: $10^{-5}$[cite: 6].\n",
    "   * Massimo iterazioni: $\\ge 8000$[cite: 6].\n",
    "3. Confronto con il Metodo del Gradiente Stocastico (SGD)[cite: 40, 41]."
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": [
    "import numpy as np\n",
    "import matplotlib.pyplot as plt\n",
    "import time\n",
    "\n",
    "def backtracking(f, df, x, alpha=1, rho=0.5, c=1e-4):\n",
    "    \"\"\"\n",
    "    Algoritmo di backtracking visto a lezione\n",
    "    \"\"\"\n",
    "    while f(x - alpha * df(x)) > f(x) - c * alpha * np.linalg.norm(df(x))**2:\n",
    "        alpha *= rho\n",
    "    return alpha\n",
    "\n",
    "def GD(f, df, x0, alpha=1e-2, maxit=8000, tolf=1e-6, tolx=1e-5, step_type='fixed', x_true=None):\n",
    "    \"\"\"\n",
    "    Metodo del Gradiente Multi-variabile [cite: 3, 5]\n",
    "    \"\"\"\n",
    "    x = x0.copy().astype(float)\n",
    "    history_f = []\n",
    "    history_grad = []\n",
    "    history_err = []\n",
    "    \n",
    "    for k in range(maxit):\n",
    "        grad = df(x)\n",
    "        grad_norm = np.linalg.norm(grad)\n",
    "        \n",
    "        # Registrazione metriche per grafici [cite: 36, 37, 38]\n",
    "        history_f.append(f(x))\n",
    "        history_grad.append(grad_norm)\n",
    "        if x_true is not None:\n",
    "            history_err.append(np.linalg.norm(x - x_true) / np.linalg.norm(x_true))\n",
    "        \n",
    "        # Scelta del passo \n",
    "        a_k = backtracking(f, df, x) if step_type == 'backtracking' else alpha\n",
    "            \n",
    "        x_new = x - a_k * grad\n",
    "        \n",
    "        # Criteri di arresto [cite: 6]\n",
    "        if grad_norm < tolf:\n",
    "            print(f\"Arresto: gradiente sotto tolleranza a k={k}\")\n",
    "            break\n",
    "        if np.linalg.norm(x_new - x) < tolx:\n",
    "            print(f\"Arresto: differenza iterati sotto tolleranza a k={k}\")\n",
    "            break\n",
    "            \n",
    "        x = x_new\n",
    "        \n",
    "    return x, np.array(history_f), np.array(history_grad), np.array(history_err)"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    "### Funzioni di Test\n",
    "Vengono definite le funzioni richieste (a, b, d, f)[cite: 8, 10, 14, 18]."
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": [
    "# (a) Quadratica semplice [cite: 8]\n",
    "def f_a(x): return (x[0]-5)**2 + (x[1]-2)**2\n",
    "def df_a(x): return np.array([2*(x[0]-5), 2*(x[1]-2)])\n",
    "x_star_a = np.array([5, 2])\n",
    "\n",
    "# (b) Rosenbrock [cite: 9, 10]\n",
    "def f_b(x): return (1-x[0])**2 + 100*(x[1]-x[0]**2)**2\n",
    "def df_b(x): \n",
    "    return np.array([-2*(1-x[0]) - 400*x[0]*(x[1]-x[0]**2), \n",
    "                     200*(x[1]-x[0]**2)])\n",
    "x_star_b = np.array([1, 1])\n",
    "\n",
    "# (d) Minimi Quadrati Lineari [cite: 14]\n",
    "def f_d(x, A, b): return 0.5 * np.linalg.norm(A @ x - b)**2\n",
    "def df_d(x, A, b): return A.T @ (A @ x - b)"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    "### Implementazione Gradiente Stocastico (SGD)\n",
    "Confronto richiesto su funzioni dei minimi quadrati[cite: 41, 42]."
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": [
    "def SGD(A, b, x0, alpha=1e-3, batch_size=10, maxit=1000, x_true=None):\n",
    "    \"\"\"\n",
    "    SGD per minimi quadrati: f(x) = 1/2 ||Ax-b||^2 [cite: 40]\n",
    "    \"\"\"\n",
    "    x = x0.copy().astype(float)\n",
    "    n_samples = A.shape[0]\n",
    "    history_err = []\n",
    "    \n",
    "    for k in range(maxit):\n",
    "        indices = np.random.choice(n_samples, batch_size, replace=False)\n",
    "        A_i = A[indices]\n",
    "        b_i = b[indices]\n",
    "        \n",
    "        grad = A_i.T @ (A_i @ x - b_i) / batch_size\n",
    "        x -= alpha * grad\n",
    "        \n",
    "        if x_true is not None:\n",
    "            history_err.append(np.linalg.norm(x - x_true) / np.linalg.norm(x_true))\n",
    "            \n",
    "    return x, np.array(history_err)"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    "### Esecuzione Esperimenti e Visualizzazione [cite: 32, 36]\n",
    "Esempio sulla funzione di Rosenbrock variando il passo."
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": [
    "x0 = np.array([-1.2, 1.0])\n",
    "alpha_tests = [0.001, 0.005]\n",
    "\n",
    "plt.figure(figsize=(14, 5))\n",
    "for a in alpha_tests:\n",
    "    _, h_f, h_g, _ = GD(f_b, df_b, x0, alpha=a, step_type='fixed')\n",
    "    \n",
    "    plt.subplot(1, 2, 1)\n",
    "    plt.plot(h_f, label=f'a={a}')\n",
    "    plt.yscale('log')\n",
    "    plt.title(\"Valore f(x) per Rosenbrock\")\n",
    "    \n",
    "    plt.subplot(1, 2, 2)\n",
    "    plt.plot(h_g, label=f'a={a}')\n",
    "    plt.yscale('log')\n",
    "    plt.title(\"Norma Gradiente\")\n",
    "\n",
    "plt.legend()\n",
    "plt.show()"
   ]
  }
 ],
 "metadata": {
  "kernelspec": {
   "display_name": "Python 3",
   "language": "python",
   "name": "python3"
  },
  "language_info": {
   "codemirror_mode": {
    "name": "ipython",
    "version": 3
   },
   "file_extension": ".py",
   "mimetype": "text/x-python",
   "name": "python",
   "nbconvert_exporter": "python",
   "pygments_lexer": "ipython3",
   "version": "3.8.10"
  }
 },
 "nbformat": 4,
 "nbformat_minor": 4
}