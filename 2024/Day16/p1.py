# MADE WITH HELP: https://www.youtube.com/watch?v=BJhpteqlVPM

import heapq

with open("in.txt") as file:
    lines = file.readlines()
    data = []
    sx = 0
    sy = 0

    for i in range(len(lines)):
        for j in range(len(lines[i])):
            if lines[i][j] == "S":
                sx = j
                sy = i

        data.append(lines[i].replace("\n", ""))

q = [(0, sx, sy, 1, 0)]
seen = set()

while q:
    cost, x, y, dx, dy = heapq.heappop(q)
    seen.add((x, y, dx, dy))

    if data[y][x] == "E":
        print(cost)
        break

    for ncost, nx, ny, ndx, ndy in [(cost + 1, x + dx, y + dy, dx, dy), (cost + 1000, x, y, dy, -dx), (cost + 1000, x, y, -dy, dx)]:
        if data[ny][nx] == "#":
            continue
        if (nx, ny, ndx, ndy) in seen:
            continue

        heapq.heappush(q, (ncost, nx, ny, ndx, ndy))
