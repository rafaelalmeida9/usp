import math

x = float(input("Digite um número: "))
x0 = float(input("Digite um chute inicial: "))
xi = x0

xi = (x0 + x/x0)/2

while math.fabs(xi - x0) > 0.00000001:
    x0 = xi
    xi = (x0 + x/x0)/2

print(xi);