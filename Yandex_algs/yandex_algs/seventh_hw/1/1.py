N = int(input())

ops = []
colored = 1
uncolored = -1
for i in range(N):
    l, r = map(int, input().split())

    ops.append((l, colored))
    ops.append((r, uncolored))

ops.sort()

ans = 0
first_inp = 0
layers = 0
for i in range(len(ops)):
    if ops[i][1] == uncolored:
        layers -= 1
        if layers == 0:
            ans += ops[i][0]-ops[first_inp][0]
    else:
        if layers == 0:
            first_inp = i
        layers += 1

print(ans)
