with open("in.txt") as file:
    data = list(map(lambda x: x.replace("\n", "").split("   "), file.readlines()))
    d1 = []
    d2 = []

    for x in data:
        d1.append(int(x[0]))
        d2.append(int(x[1]))

d1 = sorted(d1)
d2 = sorted(d2)

dist = 0

for i in range(len(d1)):
    dist += abs(d1[i] - d2[i])

print(dist)
