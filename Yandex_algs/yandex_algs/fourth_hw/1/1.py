n = int(input())

colors = {}

for i in range(n):
    color, val = map(int, input().split())

    if color not in colors:
        colors[color] = 0

    colors[color] += val

for i in sorted(colors.keys()):
    print(i, end=' ')
    print(colors[i])
