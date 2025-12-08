with open("in.txt") as file:
    data = [list(map(lambda x: int(x), line.split(","))) for line in file.readlines()]


min_distances = []

for i in range(len(data)):
    for j in range(len(data)):
        if i != j:
            dist = ((data[i][0] - data[j][0]) ** 2 + (data[i][1] - data[j][1]) ** 2 + (data[i][2] - data[j][2]) ** 2) ** 0.5
            min_distances.append((data[i], data[j], dist))


min_distances.sort(key=lambda x: x[2])

circuits = []
result = 0

for i in range(len(min_distances)):
    [p1, p2, dist] = min_distances[i]
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

    circuits.sort(key=lambda x: -len(x))

    if len(circuits[0]) == len(data):
        result = p1[0] * p2[0]
        break
    
print(result)
