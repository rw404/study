m = int(input())

parts = []

start = 0
end = 1
while True:
    l, r = map(int, input().split())
    if l == 0 and r == 0:
        break

    parts.append((l, r))

parts.sort()

#print(parts)
ans = []

stop = len(parts)
i = 0

median = 0

while i < stop and parts[i][1] <= median:
    i += 1

end = parts[i][1]
first_ans = parts[i]

while i < stop and parts[i][0] <= median and parts[i][1] > median:
    if parts[i][1] > end:
        end = parts[i][1]
        first_ans = parts[i]
    i+= 1

ans.append(first_ans)
median = end

cnt = 1

#print(i)
#print(ans)

while i < stop:
    if parts[i][0] >= m or median > m:
        break
    to_ans = parts[i]
    end = median
    loop = False
    while i < stop and parts[i][1] < median and parts[i][0] < median:
        i += 1
        loop = True

    if i == stop or parts[i][0] > median:
        break

    while i < stop and parts[i][0] <= median: 
        #print(f'$$$$$$ {parts[i]}')
        if parts[i][1] > end:
            end = parts[i][1]
            to_ans = parts[i]
        i += 1
        loop = True
    #print(f'i<stop: {i<stop} parts[i][1]>=median: {parts[i][1] >= median} parts[i][0]<=median: {parts[i][0]<=median} {parts[i]} {median}')
    #print(f'###### {to_ans} {to_ans[1]}')

    if to_ans[0] >= m:
        break
    if to_ans[1] > ans[-1][1]:
        ans.append(to_ans)
        median = to_ans[1]
        cnt += 1
    if loop:
        i -= 1
    i+= 1

#print(ans)

if ans[0][0] > 0 or ans[-1][0] >= m or ans[-1][1] < m:
    print("No solution")
else:
    print(cnt)
    for i in ans:
        print(f'{i[0]} {i[1]}')
