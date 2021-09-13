N, i, j = map(int, input().split())

first_way = abs(j-i)

second_way = N - first_way - 1

first_way -= 1

if first_way < second_way:
    print(first_way)
else:
    print(second_way)
