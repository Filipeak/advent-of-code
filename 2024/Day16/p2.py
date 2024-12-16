# MADE WITH HELP: https://www.youtube.com/watch?v=BJhpteqlVPM

import heapq
from collections import deque

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
lowest_cost = {(sx, sy, 1, 0): 0}
backtrack = {}
best_cost = float("inf")
end_states = set()

while q:
    cost, x, y, dx, dy = heapq.heappop(q)

    if cost > lowest_cost.get((x, y, dx, dy), float("inf")):
        continue

    if data[y][x] == "E":
        if cost > best_cost:
            break

        best_cost = cost
        end_states.add((x, y, dx, dy))

    for ncost, nx, ny, ndx, ndy in [(cost + 1, x + dx, y + dy, dx, dy), (cost + 1000, x, y, dy, -dx), (cost + 1000, x, y, -dy, dx)]:
        if data[ny][nx] == "#":
            continue

        lowest = lowest_cost.get((nx, ny, ndx, ndy), float("inf"))

        if ncost > lowest:
            continue
        if ncost < lowest:
            backtrack[(nx, ny, ndx, ndy)] = set()
            lowest_cost[(nx, ny, ndx, ndy)] = ncost

        backtrack[(nx, ny, ndx, ndy)].add((x, y, dx, dy))
        heapq.heappush(q, (ncost, nx, ny, ndx, ndy))

states = deque(end_states)
seen = set(end_states)

while states:
    s = states.popleft()

    for last in backtrack.get(s, []):
        if last in seen:
            continue

        seen.add(last)
        states.append(last)

final = {(x, y) for x, y, _, _ in seen}

print(len(final))
