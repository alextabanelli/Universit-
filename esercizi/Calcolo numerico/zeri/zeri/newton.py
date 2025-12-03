
from numpy import cos,sin

def newton(f,Df,x0,errorTol,errorTol2,maxIter=20):
    
    x=x0 
    errorestimate=1
    functionestimate=1
    k=0
    while (errorestimate >= errorTol or functionestimate >= errorTol2 and  k<maxIter):
        fx=f(x)
        Dfx=Df(x)
        x-=fx/Dfx
        errorestimate=abs(fx/Dfx)
        functionestimate=abs(fx)
        k=k+1
    return(x,errorestimate,functionestimate,k)

def f(x):
    return x-cos(x)

def Df(x):
    return 1.+cos(x)

x0=1.
(zero,error,functionvalue,iterations)=newton(f,Df,x0,1.e-6,1.e-7)

print(zero,error,functionvalue,iterations)