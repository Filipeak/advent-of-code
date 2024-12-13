with open("in.txt") as file:
    rawData = file.readlines()
    data = []

    data.append([])

    for line in rawData:
        if line == "\n":
            data.append([])
        else:
            rawCoords = line.replace("\n", "").split(": ")[1]
            coords = rawCoords.split(", ")
            data[-1].append((int(coords[0][2:]), int(coords[1][2:])))


tokens = 0

for x in data:
    btn_a = x[0]
    btn_b = x[1]
    dest = (x[2][0] + 10000000000000, x[2][1] + 10000000000000)

    a1 = btn_a[0]
    a2 = btn_a[1]
    b1 = btn_b[0]
    b2 = btn_b[1]
    c1 = -dest[0]
    c2 = -dest[1]

    n_b = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1)
    n_a = (-b1 * n_b - c1) / a1

    if int(n_b) == n_b and int(n_a) == n_a:
        tokens += int(n_a) * 3 + int(n_b)

print(tokens)
