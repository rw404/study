N = int(input())

names_idxs = {}
lines = {}
heights = {}
parents = {}

root = [] 
for i in range(N-1):
    child, father = input().split()

    if child not in names_idxs:
        names_idxs[child] = 0
    names_idxs[child] += 1

    if child not in parents:
        parents[child] = []
    parents[child].append(father)

    if father not in lines:
        lines[father] = []
    lines[father].append(child)

for i in lines.keys():
    if i not in names_idxs:
        root.append(i)
        heights[i] = 0

front_walk = root

for i in range(N):
    if front_walk[i] not in lines:
        continue
    for j in range(len(lines[front_walk[i]])):
        front_walk.append(lines[front_walk[i]][j])
        heights[lines[front_walk[i]][j]] = heights[front_walk[i]]+1

def parents_fnd(prs, el):
    if el in prs and prs[el] == 1:
        print(el)
        return prs
    if el not in prs:
        prs[el] = 1
    pars = [el]
    end = len(pars)
    j = 0
    while j < end:
        if pars[j] not in parents:
            return prs
        for i in parents[pars[j]]:
            pars.append(i)
            end += 1
            if i not in prs:
                prs[i] = 0
            if prs[i] == 1:
                print(i)
                return prs
            prs[i] = 1
        j += 1

while True:
    try:
        first, second = input().split()
    except EOFError:
        break

    if heights[first] > heights[second]:
        prs = parents_fnd({}, second)
        ans = parents_fnd(prs, first)
    else:
        prs = parents_fnd({}, first)
        ans = parents_fnd(prs, second)

