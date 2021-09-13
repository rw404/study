inp = input()
l = inp.__len__()

ans = 0
for i in range(l//2):
    if inp[i] != inp[l-1-i]:
        ans += 1

print(ans)
