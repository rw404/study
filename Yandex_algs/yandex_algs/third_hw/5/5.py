M = int(input())

sets = [set() for i in range(M)]

for i in range(M):
    cur = input()
    for j in range(len(cur)):
        sets[i].add(cur[j])

N = int(input())

nums = list()
same = [0 for i in range(N)]

maxim = 0

for i in range(N):
    cur = input()
    nums.append(cur)
    for j in range(M):
        in_this = True

        for k in sets[j]:
            if k not in cur:
                in_this = False

        if in_this:
            same[i] += 1
            if same[i] > maxim:
                maxim = same[i]

for i in range(N):
    if same[i] == maxim:
        print(nums[i])
