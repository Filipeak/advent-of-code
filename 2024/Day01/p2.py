with open("in.txt") as file:
    data = list(map(lambda x: x.replace("\n", "").split("   "), file.readlines()))
    d1 = []
    d2 = []

    for x in data:
        d1.append(int(x[0]))
        d2.append(int(x[1]))

d1 = sorted(d1)
d2 = sorted(d2)

score = 0

for x in d1:
    score += x * d2.count(x)

print(score)
