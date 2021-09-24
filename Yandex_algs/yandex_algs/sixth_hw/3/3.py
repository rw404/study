a, b, c, d = map(int, input().split())

eps = 0.0000001

def polinom(x):
    return a*(x**3) + b*(x**2) + c*x + d

def lbinsearch(l, r):
    while l + eps < r:
        m = (l+r)/2
        if polinom(m) > 0:
            if polinom(l) <= 0:
                r = m
            else:
                l = m
        else:
            if polinom(l) <= 0:
                l = m
            else:
                r = m

    return l

print(lbinsearch(-10000, 10000))
