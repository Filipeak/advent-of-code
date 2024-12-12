with open("in.txt") as file:
    data = list(map(lambda x: list(map(lambda y: [y, False], x.replace("\n", ""))), file.readlines()))

regions = []


def calculate_region(x, y, c):
    if data[y][x][0] != c:
        return "invalid"

    if data[y][x][1]:
        return "used"

    data[y][x][1] = True

    perimeter = 0
    dirs = [(1, 0), (0, -1), (-1, 0), (0, 1)]

    for dir in dirs:
        newX = x + dir[0]
        newY = y + dir[1]

        if newX >= 0 and newX < len(data[0]) and newY >= 0 and newY < len(data):
            if calculate_region(newX, newY, c) == "invalid":
                perimeter += 1
        else:
            perimeter += 1

    regions[-1][0] += 1
    regions[-1][1] += perimeter

    return "valid"


for i in range(len(data)):
    for j in range(len(data[i])):
        if not data[i][j][1]:
            regions.append([0, 0])

            calculate_region(j, i, data[i][j][0])

ans = 0

for x in regions:
    ans += x[0] * x[1]

print(ans)
