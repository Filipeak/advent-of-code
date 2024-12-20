import heapq

with open("in.txt") as file:
    data = [x.replace("\n", "") for x in file.readlines()]
    sr = 0
    sc = 0

    for r in range(len(data)):
        for c in range(len(data[r])):
            if data[r][c] == "S":
                sr = r
                sc = c

q = [(0, sc, sr, 0, 0)]
backtrack = {(sc, sr): None}
path = []

while q:
    d, x, y, lx, ly = heapq.heappop(q)

    if data[y][x] == "E":
        current = (x, y)
        while current != None:
            path.append(current)
            current = backtrack[current]
        path.reverse()

    for dir in [(1, 0), (0, 1), (-1, 0), (0, -1)]:
        nd = d + 1
        nx = x + dir[0]
        ny = y + dir[1]

        if nx < 0 or nx >= len(data[0]) or ny < 0 or ny >= len(data):
            continue

        if data[ny][nx] == "#":
            continue

        if (nx, ny) in backtrack:
            continue

        backtrack[(nx, ny)] = (x, y)
        heapq.heappush(q, (nd, nx, ny, x, y))

n = 0

for i in range(len(path)):
    for dir in [(1, 0), (0, 1), (-1, 0), (0, -1)]:
        nx = path[i][0] + dir[0]
        ny = path[i][1] + dir[1]

        if nx < 0 or nx >= len(data[0]) or ny < 0 or ny >= len(data):
            continue

        if data[ny][nx] == "#":
            nx2 = nx + dir[0]
            ny2 = ny + dir[1]

            if (nx2, ny2) in path and data[ny2][nx2] != "#":
                diff = path.index((nx2, ny2)) - i - 2

                if diff >= 100:
                    n += 1

print(n)