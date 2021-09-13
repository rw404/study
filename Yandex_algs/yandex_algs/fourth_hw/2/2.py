results = {}

while True:
    try:
        inp=input()
    except EOFError:
        break

    name, votes = inp.split()[0], int(inp.split()[1])

    if name not in results:
        results[name] = 0

    results[name] += votes

for i in sorted(results.keys()):
    print(i, end=' ')
    print(results[i])
