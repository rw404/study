N = int(input())

ops = []
add = 1
rem = -1

for i in range(N):
    l, d = map(int, input().split())

    ops.append((l, add))
    ops.append((l+d, rem))

ops.sort()
num = 1
online = 0

for i in range(len(ops)): 
    if ops[i][1] == add:
        online += 1
        num = max(online, num)
    else:
        online -= 1

print(num)
