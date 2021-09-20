inp = input()

summ = [0]
for i in range(len(inp)):
    if inp[i] == '(':
        summ.append(summ[-1]-1)
    elif inp[i] == ')':
        summ.append(summ[-1]+1)
        if summ[-1] > 0:
            break

if summ[-1] != 0:
    print("NO")
else:
    print("YES")
