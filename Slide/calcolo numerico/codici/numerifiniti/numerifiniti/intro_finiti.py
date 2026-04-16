import sys

print(sys.float_info)
print(f"massimo numero floating point {sys.float_info.max}")
print(f"minimo numero floating point {sys.float_info.min}")

print('inf',1.8e+308) # ottengo un infinito
print('zero?',2.e-360) # per ottenere zero devo andare sotto esponente -354 che è il valore DENORMALIZZATO minimo


import numpy as np

print(np.spacing(1.e9)) #spaziatura fra due numeri finiti (dopo argomento)
machine_eps=np.finfo(float).eps

print(f"precisione di macchina {machine_eps}")