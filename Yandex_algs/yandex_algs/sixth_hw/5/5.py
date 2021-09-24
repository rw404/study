n, k = map(int, input().split())

inp = sorted(set(list(map(int, input().split()))))

max_len = inp[-1]-inp[0]

def check(l):
    cur = k-1
    last = inp[0]+l
    for i in range(len(inp)):
        if last < inp[i]:
            cur -= 1
            if cur < 0:
                return False
            last = inp[i]+l
    return True

def lbinsearch(l, r):
    while l < r:
        m = (l+r)//2
        if check(m):
            r = m
        else:
            l = m+1
    return l

print(lbinsearch(0, max_len))
