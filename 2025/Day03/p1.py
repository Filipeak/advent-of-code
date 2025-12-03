with open("in.txt") as f:
    data = list(map(lambda x: x.strip(), f.readlines()))

result = 0

for line in data:
    n1 = -1
    n2 = -1

    for i in range(len(line) - 1):
        a1 = int(line[i])
        a2 = int(line[i + 1])

        if a1 > n1:
            n1 = a1
            n2 = a2
        if a2 > n2:
            n2 = a2

    result += n1 * 10 + n2

print(result)