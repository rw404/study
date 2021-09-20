n, q = map(int, input().split())

elems = list(map(int, input().split()))
sums = [0]

for i in range(1, n+1):
    sums.append(elems[i-1] + sums[i-1])

for i in range(q):
    l, r = map(int, input().split())
    print(sums[r]-sums[l-1])
