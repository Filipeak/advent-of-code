with open("in.txt") as file:
    data = list(map(lambda x: x.replace("\n", ""), file.readlines()))
    ranges = []

    for line in data:
        if line == "":
            break

        tmp = line.split("-")
        ranges.append((int(tmp[0]), int(tmp[1])))


ranges.sort()

merged = []

for r in ranges:
    if len(merged) == 0 or r[0] > merged[-1][1]:
        merged.append(r)
    else:
        merged[-1] = (merged[-1][0], max(merged[-1][1], r[1]))


result = 0

for m in merged:
    result += m[1] - m[0] + 1

print(result)
