dirsDict = {">": (1, 0), "v": (0, 1), "<": (-1, 0), "^": (0, -1)}
dirs = [dirsDict[">"], dirsDict["v"], dirsDict["<"], dirsDict["^"]]

with open("in.txt") as file:
    data = file.readlines()
    startX = -1
    startY = -1
    startDirInd = -1

    for i in range(len(data)):
        data[i] = data[i].replace("\n", "")

        for j in range(len(data[i])):
            if data[i][j] in dirsDict.keys():
                startX = j
                startY = i
                startDirInd = list(dirsDict.keys()).index(data[i][j])

                break

        if startX != -1:
            break


curX = startX
curY = startY
curDirInd = startDirInd
visited = {(curX, curY)}

while True:
    tmpX = curX + dirs[curDirInd][0]
    tmpY = curY + dirs[curDirInd][1]

    if tmpX < 0 or tmpX >= len(data[0]) or tmpY < 0 or tmpY >= len(data):
        break

    if data[tmpY][tmpX] == "#":
        curDirInd = (curDirInd + 1) % 4
    else:
        curX = tmpX
        curY = tmpY

        pos = (curX, curY)

        if pos not in visited:
            visited.add(pos)

print(len(visited))
