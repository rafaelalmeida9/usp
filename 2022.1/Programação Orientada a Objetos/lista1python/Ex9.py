def f(x):
    a = 1
    b = -1
    c = -13
    d = 8

    return (a*x*x*x + b*x*x + c*x +d)

def f1(x):
    a = 3
    b = -2
    c = -13

    return (a*x*x + b*x + c)

x0 = float(input())

contador = 0

x1 = x0 - (f(x0)/f1(x0));

while(abs(x1-x0) > 0.0000001):

    x0 = x1
    x1 = x0 - (f(x0)/f1(x0));

    contador += 1

print("A raiz encontrada foi:", x1)
print("Foram realizadas", contador, "iterações")