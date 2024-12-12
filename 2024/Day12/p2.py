with open("in.txt") as file:
    data = list(map(lambda x: list(map(lambda y: [y, False], x.replace("\n", ""))), file.readlines()))

regions = []


def calculate_region(x, y, c):
    if data[y][x][0] != c or data[y][x][1]:
        return

    data[y][x][1] = True

    regions[-1][0] += 1
    regions[-1][1].append((x, y, 1))
    regions[-1][1].append((x + 1, y, 2))
    regions[-1][1].append((x + 1, y + 1, 3))
    regions[-1][1].append((x, y + 1, 4))

    dirs = [(1, 0), (0, -1), (-1, 0), (0, 1)]

    for dir in dirs:
        newX = x + dir[0]
        newY = y + dir[1]

        if newX >= 0 and newX < len(data[0]) and newY >= 0 and newY < len(data):
            calculate_region(newX, newY, c)


for i in range(len(data)):
    for j in range(len(data[i])):
        if not data[i][j][1]:
            regions.append([0, []])

            calculate_region(j, i, data[i][j][0])

ans = 0

for x in regions:
    pts = {}

    for r in x[1]:
        key = (r[0], r[1])

        if key in pts:
            pts[key].append(r[2])
        else:
            pts[key] = [r[2]]

    count = 0

    for p in pts.keys():
        point = pts[p]

        if len(point) == 1 or len(point) == 3:
            count += 1
        elif len(point) == 2:
            k1 = point[0]
            k2 = point[1]

            if abs(k1 - k2) == 2:
                count += 2

    ans += x[0] * count

print(ans)
