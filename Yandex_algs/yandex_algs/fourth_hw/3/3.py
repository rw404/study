count = {}

maximum = 0

while True:
    try:
        inp = list(input().split())
    except EOFError:
        break

    for i in inp:
        if i not in count:
            count[i] = 0
        count[i] += 1
        maximum = max(maximum, count[i])

to_out = [(maximum-count[i], i) for i in count.keys()]

ans = sorted(to_out)

for i in range(len(ans)):
    print(ans[i][1])
