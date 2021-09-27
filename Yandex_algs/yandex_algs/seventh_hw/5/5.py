N = int(input())

ops = []

pi = 3.14159265

r_out = 1000001
r_in = 0

entry = 0
out = 1
for i in range(N):
    r1, r2, p1, p2 = map(float, input().split())

    if p1 > p2:
        ops.append((p1, entry, r1, r2))
        ops.append((2*pi, out, r1, r2))
        p1 = 0
        
    ops.append((p1, entry, r1, r2))
    ops.append((p2, out, r1, r2))
    r_in = max(r_in, r1)
    r_out = min(r_out, r2)

ops.sort()

online = 0
phi_in = -100
s = 0

def s_cnt(r_in, r_out, phi):
    s_out = pi*r_out*r_out
    s_in = pi*r_in*r_in
    delta_s = s_out-s_in
    delta_s = delta_s*phi/(2*pi)

    return delta_s

for i in range(len(ops)):
    if ops[i][1] == entry:
        phi_in = max(phi_in, ops[i][0])
        online += 1
    else:
        delta_angle = ops[i][0] - phi_in 
        if online == N:
            #print(f'{r_in} {r_out} {phi_in} {ops[i][0]}')
            s = s+s_cnt(r_in, r_out, delta_angle)
        phi_in = -100
        online -= 1

print(s)
