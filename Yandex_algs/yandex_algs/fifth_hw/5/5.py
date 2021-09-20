S = int(input())

def list_inp():
    inp = list(map(int, input().split()))
    n = inp[0]
    l = inp[1:]
    return n, l

def create_dict(l):
    ans = {}
    for i in range(len(l)):
        if l[i] not in ans:
            ans[l[i]] = i
    
    return ans

n_a, a = list_inp()
n_b, b = list_inp()
n_c, c = list_inp()
c = create_dict(c)

found = False

for i in range(len(a)):
    for j in range(len(b)):
        val = S - a[i] - b[j]
        if not found and val > 0 and val in c:
            print(i, end=' ')
            print(j, end=' ')
            print(c[val])
            found = True

if not found:
    print(-1)
