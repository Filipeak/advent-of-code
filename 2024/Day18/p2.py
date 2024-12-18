import heapq
import math

with open("in.txt") as file:
    pts = [list(map(lambda y: int(y), x.replace("\n", "").split(","))) for x in file.readlines()]


def is_reachable(n):
    MAP_X = 71
    MAP_Y = 71

    q = [(0, 0, 0)]
    seen = set()

    while q:
        d, x, y = heapq.heappop(q)
        seen.add((x, y))

        if x == MAP_X - 1 and y == MAP_Y - 1:
            return True

        for dir in [(1, 0), (0, 1), (-1, 0), (0, -1)]:
            nd = d + 1
            nx = x + dir[0]
            ny = y + dir[1]

            if nx < 0 or nx >= MAP_X or ny < 0 or ny >= MAP_Y:
                continue

            border = False
            for i in range(n):
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

    return False


n = int(len(pts) / 2)
d = n
while True:
    if int(d) == 0:
        print(f"{pts[n-1][0]},{pts[n-1][1]}")
        break

    if is_reachable(n):
        n += math.ceil(d / 2)
    else:
        n -= math.ceil(d / 2)
    d = d / 2
