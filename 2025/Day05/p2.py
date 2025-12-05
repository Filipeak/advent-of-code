with open("in.txt") as file:
    data = list(map(lambda x: x.replace("\n", ""), file.readlines()))
    ranges = []

    for line in data:
        if line == "":
            break

        tmp = line.split("-")
        ranges.append((int(tmp[0]), int(tmp[1])))


unique_ranges = []

for r in ranges:
    tmp = [r]

    for u in unique_ranges:
        i = 0

        while i < len(tmp):
            t = tmp[i]

            # Complete Overlap, split into two ignoring the center
            if t[0] < u[0] and t[1] > u[1]:
                nr1 = (t[0], u[0] - 1)
                nr2 = (u[1] + 1, t[1])
                tmp[i] = nr1
                tmp.append(nr2)
                i += 1

            # Complete inside, ignore
            elif u[0] <= t[0] and u[1] >= t[1]:
                tmp.remove(t)

            # Left side
            elif t[0] < u[0] and t[1] >= u[0]:
                nr = (t[0], u[0] - 1)
                tmp[i] = nr

            # Right side
            elif t[1] > u[1] and t[0] <= u[1]:
                nr = (u[1] + 1, t[1])
                tmp[i] = nr

            # Do not overlap
            else:
                pass

            i += 1

    unique_ranges.extend(tmp)


result = 0

for u in unique_ranges:
    result += u[1] - u[0] + 1

print(result)
