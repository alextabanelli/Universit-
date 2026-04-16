
import numpy as np

# implementa il limite (1+1/n)^n

esp=np.logspace(0,16,17)
for i in range(0,17):
   s=(1+1/esp[i])**esp[i]
   print("i=",i,"s=",np.exp(1)-s)
