# calcolo del punto fisso della funzione f(x)=x-cos(x) con g(x)=cos(x)
# e visualizzazione del percorso

import numpy as np
from matplotlib import pyplot as plt

from numpy import cos

def f_1(x): return x - cos(x)
def g_1(x): return cos(x)

g=g_1
a=0
b=1
x=np.linspace(a,b)
iterations=10

#Start at left

x_k=a
plt.figure()
plt.title ("iterazioni di punto fisso")
plt.plot(x,x,'g')
plt.plot(x,g(x),'r')
for k in range(iterations):
     g_x_k=g(x_k)
     plt.plot([x_k,x_k], [x_k,g(x_k)],'b')
     x_k_plus_1=g(x_k)
     #connect the new x_k on the line y=x
     plt.plot([x_k,g(x_k)],[x_k_plus_1,x_k_plus_1],'b')
     x_k=x_k_plus_1
     print(f"x_{k+1}={x_k_plus_1}")
plt.show()