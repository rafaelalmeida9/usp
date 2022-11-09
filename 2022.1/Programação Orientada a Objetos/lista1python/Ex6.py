x = int(input())

for i in range(x-1,1,-1):
    div = 0
    for j in range(1,i+1):
        if i%j == 0:
            div += 1
    if div == 2:
        print("O primeiro primo menor que", x, "é:", i)
        exit()