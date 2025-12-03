import numpy as np
from scipy import optimize
f=lambda x: np.cos(x)-x
r=optimize.fsolve(f,-2)
print("r=",r)

#verify that the solution is a root
result=f(r)
print("result=",result)

f1=lambda x: 1/x
r1,a,b,c=optimize.fsolve(f1,-2,full_output=True)

result1=f1(r1)
print("result=",result1,'a=',a,'b=',b,'c=',c)