def ans(l, count, steps):
    left_part = -1
    right_part = l

    half = l/2
    for i in steps:
        if i < half and i > left_part:
            left_part = i
            if i*2+1 == l:
                return left_part, left_part
        if i >= half and i < right_part:
            right_part = i

    if right_part == l:
        right_part = left_part

    return left_part, right_part

l, count = map(int, input().split())

steps = list(map(int, input().split()))

l_ans, r_ans = ans(l, count, steps)

if l_ans == r_ans:
    print(l_ans)
else:
    print(l_ans, end=" ")
    print(r_ans)
