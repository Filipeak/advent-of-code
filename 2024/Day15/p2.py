with open("in.txt") as file:
    lines = file.readlines()

    warehouseMap = []
    instructions = ""
    currentPos = ()

    for i in range(len(lines)):
        if lines[i][0] == "#":
            tmp = []

            curX = 0
            for j in range(len(lines[i])):
                c = lines[i][j]

                if c == "#":
                    tmp.append("#")
                    tmp.append("#")
                elif c == "O":
                    tmp.append("[")
                    tmp.append("]")
                elif c == ".":
                    tmp.append(".")
                    tmp.append(".")
                elif c == "@":
                    tmp.append(".")
                    tmp.append(".")

                    currentPos = (curX, i)

                curX += 2

            warehouseMap.append(tmp)
        elif lines[i][0] != "\n":
            instructions += lines[i].replace("\n", "")

moveMap = {">": (1, 0), "v": (0, 1), "<": (-1, 0), "^": (0, -1)}


def is_movable(x1, x2, y, dir):
    if warehouseMap[y + dir][x1] == "#" or warehouseMap[y + dir][x2] == "#":
        return False

    if warehouseMap[y + dir][x1] == "[" and warehouseMap[y + dir][x2] == "]":
        return is_movable(x1, x2, y + dir, dir)

    x1Valid = True
    x2Valid = True

    if warehouseMap[y + dir][x1] == "]":
        x1Valid = is_movable(x1 - 1, x2 - 1, y + dir, dir)

    if warehouseMap[y + dir][x2] == "[":
        x2Valid = is_movable(x1 + 1, x2 + 1, y + dir, dir)

    return x1Valid and x2Valid


def move(x1, x2, y, dir):
    if warehouseMap[y + dir][x1] == "#" or warehouseMap[y + dir][x2] == "#":
        return

    if warehouseMap[y + dir][x1] == "[" and warehouseMap[y + dir][x2] == "]":
        move(x1, x2, y + dir, dir)

    if warehouseMap[y + dir][x1] == "]":
        move(x1 - 1, x2 - 1, y + dir, dir)

    if warehouseMap[y + dir][x2] == "[":
        move(x1 + 1, x2 + 1, y + dir, dir)

    warehouseMap[y + dir][x1] = warehouseMap[y][x1]
    warehouseMap[y + dir][x2] = warehouseMap[y][x2]
    warehouseMap[y][x1] = "."
    warehouseMap[y][x2] = "."


for ins in instructions:
    dir = moveMap[ins]
    newPos = (currentPos[0] + dir[0], currentPos[1] + dir[1])

    if warehouseMap[newPos[1]][newPos[0]] == "#":
        continue
    elif warehouseMap[newPos[1]][newPos[0]] in ["[", "]"]:
        if dir[1] == 0:
            tmpPos = newPos
            positions = [tmpPos]

            while warehouseMap[tmpPos[1]][tmpPos[0]] != "#":
                tmpPos = (tmpPos[0] + dir[0], tmpPos[1] + dir[1])
                positions.append(tmpPos)

                if warehouseMap[tmpPos[1]][tmpPos[0]] == ".":
                    for i in range(len(positions) - 1, 0, -1):
                        currP = positions[i]
                        prevP = positions[i - 1]

                        warehouseMap[currP[1]][currP[0]] = warehouseMap[prevP[1]][prevP[0]]

                    warehouseMap[positions[0][1]][positions[0][0]] = "."

                    currentPos = newPos

                    break
        else:
            x1 = 0
            x2 = 0

            if warehouseMap[newPos[1]][newPos[0]] == "[":
                x1 = newPos[0]
                x2 = x1 + 1
            else:
                x2 = newPos[0]
                x1 = x2 - 1

            if is_movable(x1, x2, newPos[1], dir[1]):
                move(x1, x2, newPos[1], dir[1])

                currentPos = newPos
    else:
        currentPos = newPos


score = 0

for i in range(len(warehouseMap)):
    for j in range(len(warehouseMap[i])):
        print(warehouseMap[i][j] if currentPos[0] != j or currentPos[1] != i else "@", end="")
        if warehouseMap[i][j] == "[":
            score += 100 * i + j
    print("")

print(score)
