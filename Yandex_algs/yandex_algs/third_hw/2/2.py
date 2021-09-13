inp = list(map(int, input().split()))

unique = set()

for i in inp:
    if i not in unique:
        unique.add(i)
        print("NO")
    else:
        print("YES")

