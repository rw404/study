voting = {}

firstval = 0

while True:
    try:
        inp = input()
    except EOFError:
        break

    vote = int(inp.split()[-1])
    name = inp[:-len(str(vote))]

    if name not in voting:
        voting[name] = 0
    voting[name] += vote
    firstval += vote

firstval /= 450

new_sum = 0

new_votes = {}

for i in voting.keys():
    new_sum += voting[i] // firstval
    new_votes[i] = voting[i] / firstval

cnt = 450-new_sum

if cnt > 0:
    collision = [(new_votes[i]%1, voting[i], i) for i in voting.keys()]
    ans = sorted(collision, reverse=True)
    
    print(ans)

    while cnt > 0:
        for i in ans:
            new_votes[i[2]] += 1
            cnt -= 1
            if cnt == 0:
                break

for i in new_votes.keys():
    print(i, end=' ')
    print(int(new_votes[i]//1))
