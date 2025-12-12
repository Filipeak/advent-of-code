with open("in.txt") as file:
    data = file.read().split("\n\n")

    presents = []
    regions = []

    for i in range(len(data) - 1):
        present = data[i].split("\n")[1:]
        presents.append(present)

    for tmp in data[-1].split("\n"):
        s = tmp.replace(":", "").split(" ")
        dim = (int(s[0].split('x')[0]), int(s[0].split('x')[1]))
        quantity = [int(q) for q in s[1:]]
        regions.append((dim, quantity))


presents_counts = []

for present in presents:
    count = 0

    for row in present:
        for cell in row:
            if cell == '#':
                count += 1

    presents_counts.append(count)


result = 0

for region in regions:
    dim = region[0]
    quantity = region[1]

    n_blocks = 0

    for i in range(len(quantity)):
        n_blocks += quantity[i] * presents_counts[i]

    n_3x3_grids = (dim[0] // 3) * (dim[1] // 3)

    if sum(quantity) <= n_3x3_grids:
        result += 1
        continue
    elif n_blocks > dim[0] * dim[1]:
        continue

print(result)
