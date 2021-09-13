builds = list(map(int, input().split()))
first = []
first_mag = -1
inf = 12
for i in range(10):
    if builds[i] == 2:
        first_mag = i
    elif builds[i] == 1:
        if first_mag < 0:
            first.append(inf)
        else:
            first.append(i-first_mag)

second = []
second_mag = 10
for i in range(9, -1, -1):
    if builds[i] == 2:
        second_mag = i
    elif builds[i] == 1:
        if second_mag > 9:
            second.append(inf)
        else:
            second.append(second_mag-i)

l = first.__len__();

compare = []
for i in range(l):
    
    compare.append(min(first[i], second[l-i-1]))

ans = 0

for i in range(l):
    if compare[i] > ans:
        ans = compare[i]

print(ans)
