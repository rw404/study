import numpy as np

sizes = [5, 10, 100, 1000, 5000]

for i in sizes:
    arr = np.random.normal(size = (i, i))

    file = "tests/mat_" + str(i)

    with open(file, 'w') as f:
        f.write(str(i) + '\n')
        for j in range(i):
            line = ""
            for k in range(i):
                line += str(arr[j, k])
                line += " "
            line += '\n'
            f.write(line)
