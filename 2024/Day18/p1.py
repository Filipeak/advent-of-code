import heapq

with open("in.txt") as file:
    pts = [list(map(lambda y: int(y), x.replace("\n", "").split(","))) for x in file.readlines()]

MAP_X = 71
MAP_Y = 71
N = 1024

q = [(0, 0, 0)]
seen = set()

while q:
    d, x, y = heapq.heappop(q)
    seen.add((x, y))

    if x == MAP_X - 1 and y == MAP_Y - 1:
        print(d)
        break

    for dir in [(1, 0), (0, 1), (-1, 0), (0, -1)]:
        nd = d + 1
        nx = x + dir[0]
        ny = y + dir[1]

        if nx < 0 or nx >= MAP_X or ny < 0 or ny >= MAP_Y:
            continue

        border = False
        for i in range(N):
            if pts[i][0] == nx and pts[i][1] == ny:
                border = True
                break
        if border:
            continue

        if (nx, ny) in seen:
            continue
        else:
            seen.add((nx, ny))

        heapq.heappush(q, (nd, nx, ny))
