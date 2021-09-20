N, M = map(int, input().split())

def create_dict(l):
    ans = {}
    for i in range(len(l)):
        if l[i] not in ans:
            ans[l[i]] = []
        ans[l[i]].append(i)
    return ans

def sorted_list(l):
    ans = []
    for i in sorted(l.keys()):
        for j in range(len(l[i])):
            ans.append(i)
    return ans

groups = list(map(int, input().split()))
classes = list(map(int, input().split()))

groups = create_dict(groups)
classes = create_dict(classes)

sorted_g = sorted_list(groups)
sorted_c = sorted_list(classes)

sums = [0]
for i in range(1, N+1):
    sums.append(sums[i-1]+sorted_g[i-1])

second = 0
minus = 0
prev_minus = 0
auds = [-1]*N
good = 0
last_idx = 0
min_idx = groups[sorted_g[0]][0]

for first in range(M):
    moved = False
    cnt = 1
    while second < N and sums[second+1]-minus <= sorted_c[first]-cnt:
        second += 1
        cnt += 1
        moved = True
    if second == N:
        for i in range(last_idx, second):
            auds[groups[sorted_g[i]][0]] = classes[sorted_c[first]][0]
            groups[sorted_g[i]].pop(0)
            classes[sorted_c[first]].pop(0)
            cnt -= 1
            good += 1
        prev_minus = minus
        break
    else:
        if moved:
            for i in range(last_idx, second):
                auds[groups[sorted_g[i]][0]] = classes[sorted_c[first]][0]
                classes[sorted_c[first]].pop(0)
                groups[sorted_g[i]].pop(0)
                cnt -= 1
                good += 1
            last_idx = second
            prev_minus = minus
            minus = sums[second]

#if sums[N]-prev_minus == sorted_c[M-1]:
#    auds[min_idx] = -1
#    good -= 1

print(good)
for i in range(N-1):
    print(auds[i]+1, end=' ')
print(auds[N-1]+1)
