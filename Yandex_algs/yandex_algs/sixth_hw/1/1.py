N = int(input())
inp = list(map(int, input().split()))

def lbinsearch(l, r, inp, val):
    while l < r:
        m = (l+r)//2
        if inp[m] >= val:
            r = m
        else:
            l = m+1

    return l

def rbinsearch(l, r, inp, val):
    while l < r:
        m = (l+r+1)//2
        if inp[m] <= val:
            l = m
        else:
            r = m-1

    return l

inp = sorted(inp)

K = int(input())

for i in range(K):
    L, R = map(int, input().split())
    ind_f, ind_s = lbinsearch(0, N-1, inp, L), rbinsearch(0, N-1, inp, R)

    if L > inp[-1] or R < inp[0]:
        print(0)
    else:
        print(ind_s-ind_f+1)


