inp = list(map(int, input().split()))

unique = set()

ans = list()

for i in inp:
    if i not in unique:
        unique.add(i)
        ans.append(i)
    else:
        if i in ans:
            ans.remove(i)

for i in ans:
    print(i, end=' ')

print()
