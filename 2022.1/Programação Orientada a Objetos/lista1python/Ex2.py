import math

a = float(input())
b = float(input())
c = float(input())

delta = b**2 - 4*a*c

if delta<0:
    print("Delta negativo, não existem raízes reais\n");
else:
    x1 = (-1*b + math.sqrt(delta))/(2*a)
    x2 = (-1*b - math.sqrt(delta))/(2*a)

    print("a raiz x1 vale: ", x1, " e a raiz x2 vale: ", x2)