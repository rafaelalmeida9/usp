maxv = -999999999.0
minv = 999999999.0

while(True):
    x = float(input())
    if(x == 0):
        break

    maxv = max(x,maxv)
    minv = min(x,minv)

print("O maior número da sequência é:", maxv)
print("O menor número da sequência é:", minv)