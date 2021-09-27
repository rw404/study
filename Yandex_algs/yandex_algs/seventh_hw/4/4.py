n, m = map(int, input().split())

cats = list(map(int, input().split()))
cats.sort()
max_cat_idx = len(cats)

ops = []
beg = -1
end = 1
for i in range(m):
    l, r = map(int, input().split())

    ops.append((l, beg, i))
    ops.append((r, end, i))

ans = [0]*m

ops.sort()

cat_idx = 0
current_max = 0
online = 0

for i in range(len(ops)):
    if ops[i][1] == beg:
        online += 1
        while cat_idx < max_cat_idx and cats[cat_idx] < ops[i][0]:
            cat_idx += 1
            current_max += 1
        ans[ops[i][2]] = current_max
    else:
        while cat_idx < max_cat_idx and cats[cat_idx] <= ops[i][0]:
            cat_idx += 1
            current_max += 1
        online -= 1
        ans[ops[i][2]] = current_max - ans[ops[i][2]]

for i in range(m-1):
    print(ans[i], end=' ')
print(ans[-1])
