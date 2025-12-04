with open("in.txt") as file:
    data = list(map(lambda x: x.strip(), file.readlines()))

nodes = set()

for r in range(len(data)):
    for c in range(len(data[r])):
        if data[r][c] == '@':
            nodes.add((r, c))

result = 0

while True:
    tmp_removed = []

    for (r, c) in nodes:
        count = 0

        for dir in [(-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1)]:
            if (r + dir[0], c + dir[1]) in nodes:
                count += 1

        if count < 4:
            tmp_removed.append((r, c))

    if len(tmp_removed) == 0:
        break
    else:
        for n in tmp_removed:
            nodes.remove(n)

        result += len(tmp_removed)

print(result)
