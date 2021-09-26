N = int(input())

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

inp = list(map(int, input().split()))

M = int(input())
check = list(map(int, input().split()))

for i in range(M):
    if check[i] < inp[0] or check[i] > inp[-1]:
        print("0 0")
    else:
        left, right = lbinsearch(0, N-1, inp, check[i])+1, rbinsearch(0, N-1, inp, check[i])+1
        if left > right:
            print("0 0")
        else:
            print(f'{left} {right}')
