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
            valid = False

            n = 1
            while True:
                c = (freqs[i][1] + n * dx, freqs[i][2] + n * dy)

                if c[0] >= 0 and c[0] <= maxX and c[1] >= 0 and c[1] <= maxY:
                    coords.add(c)
                    valid = True
                else:
                    break

                n += 1

            n = 1
            while True:
                c = (freqs[j][1] - n * dx, freqs[j][2] - n * dy)

                if c[0] >= 0 and c[0] <= maxX and c[1] >= 0 and c[1] <= maxY:
                    coords.add(c)
                    valid = True
                else:
                    break

                n += 1

for x in freqs:
    coords.add((x[1], x[2]))

print(len(coords))
