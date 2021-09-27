N = int(input())

names_idxs = {}
sons_num = {}
lines = {}
heights = {}

root = [] 
for i in range(N-1):
    child, father = input().split()

    if child not in names_idxs:
        names_idxs[child] = 0
    names_idxs[child] += 1

    if father not in sons_num:
        sons_num[father] = 0
    sons_num[father] += 1

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

def search(node, el):
    if node not in lines:
        return False
    for i in range(len(lines[node])):
        if el == lines[node][i]:
            return True
        if search(lines[node][i], el):
            return True
    return False

while True:
    try:
        first, second = input().split()
    except EOFError:
        break

    if first not in heights or second not in heights:
        print(0, end=' ')
    elif heights[first] == heights[second]:
        print(0, end=' ')
    elif heights[first] < heights[second]:
        if search(first, second):
            print(1, end=' ')
        else:
            print(0, end=' ')
    else:
        if search(second, first):
            print(2, end=' ')
        else:
            print(0, end=' ')
