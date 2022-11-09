x = int(input())

div = 0
minDiv = 99999999

for i in range(2,x+1):
    if x%i == 0:
        div += 1
        minDiv = min(minDiv,i)

if div == 1:
    print("O número ", x, " é primo")
else:
    print("O número ", x, " não é primo")
    print("Seu menor divisor é o ", minDiv)