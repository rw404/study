d = int(input())
x, y = map(int, input().split())

if 0 <= x and x <= d and 0 <= y and y <= d and y <= d-x:
    print(0)
else:
    to_A = x**2+y**2
    to_B = (x-d)**2+y**2
    to_C = x**2+(y-d)**2

    if to_A <= to_B and to_A <= to_C:
        print(1)
    elif to_B <= to_A and to_B <= to_C:
        print(2)
    else:
        print(3)
