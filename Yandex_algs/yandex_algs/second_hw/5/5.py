def time(N, arr):
    max_size = 0
    summ = 0

    for i in arr:
        if i > max_size:
            max_size = i
        summ += i

    summ -= max_size;
    
    return summ

N = int(input())
array = list(map(int, input().split()))

print(time(N, array))
