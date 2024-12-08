with open("in.txt") as file:
    lines = file.readlines()
    freqs = []

    for i in range(len(lines)):
        lines[i] = lines[i].replace("\n", "")

        for j in range(len(lines[i])):
            if lines[i][j] != ".":
                freqs.append((lines[i][j], j, i))

maxX = len(lines[0]) - 1
maxY = len(lines) - 1
coords = set()

for i in range(len(freqs)):
    for j in range(len(freqs)):
        if i != j and freqs[i][0] == freqs[j][0]:
            dx = freqs[i][1] - freqs[j][1]
            dy = freqs[i][2] - freqs[j][2]

            c1 = (freqs[i][1] + dx, freqs[i][2] + dy)
            c2 = (freqs[j][1] - dx, freqs[j][2] - dy)

            if c1[0] >= 0 and c1[0] <= maxX and c1[1] >= 0 and c1[1] <= maxY:
                coords.add(c1)
            if c2[0] >= 0 and c2[0] <= maxX and c2[1] >= 0 and c2[1] <= maxY:
                coords.add(c2)


print(len(coords))
