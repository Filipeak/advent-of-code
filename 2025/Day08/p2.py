from heapq import heapify, heappush, heappop

with open("in.txt") as file:
    data = [list(map(lambda x: int(x), line.split(","))) for line in file.readlines()]


min_distances = []
heapify(min_distances)

for i in range(len(data)):
    for j in range(i + 1, len(data)):
        dist = ((data[i][0] - data[j][0]) ** 2 + (data[i][1] - data[j][1]) ** 2 + (data[i][2] - data[j][2]) ** 2) ** 0.5
        heappush(min_distances, (dist, i, j))


circuits = []
result = 0

for i in range(len(min_distances)):
    [dist, p1, p2] = heappop(min_distances)
    c1 = None
    c2 = None

    for c in circuits:
        if p1 in c and p2 not in c:
            c1 = c
        elif p1 not in c and p2 in c:
            c2 = c
        elif p1 in c and p2 in c:
            break
    else:
        if c1 is not None and c2 is None:
            c1.append(p2)
        elif c1 is None and c2 is not None:
            c2.append(p1)
        elif c1 is not None and c2 is not None:
            c1.extend(c2)
            circuits.remove(c2)
        else:
            circuits.append([p1, p2])

    for c in circuits:
        if len(c) == len(data):
            result = data[p1][0] * data[p2][0]
            break

    if result != 0:
        break

print(result)
