with open("in.txt") as file:
    lines = file.readlines()

    warehouseMap = []
    instructions = ""
    currentPos = ()

    for i in range(len(lines)):
        if lines[i][0] == "#":
            tmp = []

            for j in range(len(lines[i])):
                c = lines[i][j]

                if c == "@":
                    c = "."
                    currentPos = (j, i)
                if c != "\n":
                    tmp.append(c)

            warehouseMap.append(tmp)
        elif lines[i][0] != "\n":
            instructions += lines[i].replace("\n", "")


moveMap = {">": (1, 0), "v": (0, 1), "<": (-1, 0), "^": (0, -1)}

for ins in instructions:
    dir = moveMap[ins]
    newPos = (currentPos[0] + dir[0], currentPos[1] + dir[1])

    if warehouseMap[newPos[1]][newPos[0]] == "#":
        continue
    elif warehouseMap[newPos[1]][newPos[0]] == "O":
        tmpPos = newPos

        while warehouseMap[tmpPos[1]][tmpPos[0]] != "#":
            tmpPos = (tmpPos[0] + dir[0], tmpPos[1] + dir[1])

            if warehouseMap[tmpPos[1]][tmpPos[0]] == ".":
                warehouseMap[newPos[1]][newPos[0]] = "."
                warehouseMap[tmpPos[1]][tmpPos[0]] = "O"
                currentPos = newPos

                break
    else:
        currentPos = newPos


score = 0

for i in range(len(warehouseMap)):
    for j in range(len(warehouseMap[i])):
        print(warehouseMap[i][j], end="")
        if warehouseMap[i][j] == "O":
            score += 100 * i + j
    print("")

print(score)
