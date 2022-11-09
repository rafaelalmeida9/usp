def f(x):
    a = 1
    b = -1
    c = -13
    d = 8

    return (a*x*x*x + b*x*x + c*x +d)

a = float(input())
b = float(input())

c = (a+b)/2
contador = 0

while(abs(a-b) > 0.0000001):

    if(f(c) * f(a) < 0):
        b = c
        c = (a+b)/2
    else:
        a = c
        c = (a+b)/2

    contador += 1

print("A raiz encontrada no intervalo dado foi:", c)
print("Foram realizadas", contador, "iterações")