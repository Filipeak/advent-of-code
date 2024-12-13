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
    dest = x[2]

    for b in range(100, -1, -1):
        for a in range(101):
            if btn_a[0] * a + btn_b[0] * b == dest[0] and btn_a[1] * a + btn_b[1] * b == dest[1]:
                tokens += a * 3 + b
                break

print(tokens)
