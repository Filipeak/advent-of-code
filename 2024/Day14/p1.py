with open("in.txt") as file:
    lines = file.readlines()
    data = []

    for line in lines:
        factors = line.replace("\n", "").replace("p", "").replace("v", "").replace("=", "").split(" ")
        pos = factors[0].split(",")
        vel = factors[1].split(",")
        data.append(((int(pos[0]), int(pos[1])), (int(vel[0]), int(vel[1]))))

MAP_X = 101
MAP_Y = 103

quads = [0, 0, 0, 0]

for x in data:
    px = x[0][0]
    py = x[0][1]
    vx = x[1][0]
    vy = x[1][1]

    newPx = (px + vx * 100) % MAP_X
    newPy = (py + vy * 100) % MAP_Y

    if newPx < (MAP_X - 1) / 2:
        if newPy < (MAP_Y - 1) / 2:
            quads[1] += 1
        elif newPy > (MAP_Y - 1) / 2:
            quads[2] += 1
    elif newPx > (MAP_X - 1) / 2:
        if newPy < (MAP_Y - 1) / 2:
            quads[0] += 1
        elif newPy > (MAP_Y - 1) / 2:
            quads[3] += 1

total = quads[0] * quads[1] * quads[2] * quads[3]

print(total)