A, K, B, M, X = map(int, input().split())

def check(x):
    return A*x+B*x-A*(x//K)-B*(x//M) >= X

def lbinsearch(l, r):
    while l < r:
        m = (l+r)//2
        if check(m):
            r = m
        else:
            l = m+1

    return l

print(lbinsearch(0,X))
