N = int(input())

topics = {}

maximum = 0

for i in range(N):
    typ = int(input())
    if typ == 0:
        theme = input()
        if theme not in topics:
            topics[theme] = [1, [i+1]]
            maximum = max(maximum, 1)
    else:
        for j in topics.keys():
            if typ in topics[j][1]:
                topics[j][1].append(i+1)
                topics[j][0] += 1
        
                maximum = max(maximum, topics[j][0])
    text = input()

for i in topics.keys():
    if topics[i][0] == maximum:
        print(i)
        break
                
