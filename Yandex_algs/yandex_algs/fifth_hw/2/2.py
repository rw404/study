n = int(input())

elems = list(map(int, input().split()))

sums = [0]
ans = elems[0]
for i in elems:
    ans = max(ans, i)

maximum = elems[0]
minimum = 0

changed = False

for i in range(1, n+1):
    sums.append(elems[i-1]+sums[i-1])
    if sums[i] < minimum:
        if changed:
            ans = max(ans, maximum-minimum)
        maximum = minimum = sums[i]
        changed = False
    elif sums[i] > maximum:
        maximum = sums[i]
        changed = True

if changed:
    ans = max(ans, maximum - minimum)

print(ans)
