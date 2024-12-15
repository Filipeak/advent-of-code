from math import floor


with open("in.txt") as file:
    lines = file.readlines()
    data = []

    for line in lines:
        factors = line.replace("\n", "").replace("p", "").replace("v", "").replace("=", "").split(" ")
        pos = factors[0].split(",")
        vel = factors[1].split(",")
        data.append([[int(pos[0]), int(pos[1])], [int(vel[0]), int(vel[1])]])

MAP_X = 101
MAP_Y = 103

for i in range(100000):
    s = []

    for j in range(MAP_Y):
        tmp = []

        for k in range(MAP_X):
            tmp.append(0)

        s.append(tmp)

    for x in data:
        x[0][0] = (x[0][0] + x[1][0]) % MAP_X
        x[0][1] = (x[0][1] + x[1][1]) % MAP_Y

        s[x[0][1]][x[0][0]] += 1

    l = 0

    centerY = int((MAP_Y - 1) / 2)
    centerX = int((MAP_X - 1) / 2)
    stepY = floor((MAP_Y - 1) / 4)
    stepX = floor((MAP_X - 1) / 4)

    for j in range(centerY - stepY, centerY + stepY + 1):
        for k in range(centerX - stepX, centerX + stepX + 1):
            l += s[j][k]

    patternDetected = l / len(data) >= 0.6

    if patternDetected:
        print(f"==================== i = {i + 1}")

        for j in range(MAP_Y):
            for k in range(MAP_X):
                print("#" if s[j][k] > 0 else " ", end="")

            print("")
