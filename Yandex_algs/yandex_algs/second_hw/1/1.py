ans = 0
maxim = 0

while True:
    num = int(input())

    if num == 0:
        break

    if num > maxim:
        maxim = num
        ans = 1
    elif num == maxim:
        ans += 1

print(ans)
