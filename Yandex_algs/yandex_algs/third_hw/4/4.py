N = int(input())

ans = set(range(1, N+1))

while True:
    string = input()
    if string == "HELP":
        break

    inps = set(map(int, string.split()))
    res = input()

    if res == "YES":
        if len(ans) < len(inps):
            ans = inps.intersection(ans)
        else:
            ans = ans.intersection(inps)
    elif res == "NO":
        if len(inps) == 1:
            tmp = inps.pop()
            if tmp in ans:
                ans.remove(tmp)
        else:
            ans = ans.difference(inps)

ans = sorted(ans)

for i in ans:
    print(i, end=' ')
