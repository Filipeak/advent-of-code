with open("in.txt") as file:
    lines = file.readlines()
    schematics = [[]]

    for line in lines:
        if line == "\n":
            schematics.append([])
        else:
            schematics[-1].append(line.strip())

locks = []
keys = []

for schematic in schematics:
    tmp = []
    for c in range(len(schematic[0])):
        n = 0
        for r in range(len(schematic)):
            if schematic[r][c] == '#':
                n += 1
        tmp.append(n - 1)

    if '.' not in schematic[0]:
        locks.append(tmp)
    else:
        keys.append(tmp)


fit = 0

for lock in locks:
    for key in keys:
        for i in range(len(key)):
            if key[i] + lock[i] > 5:
                break
        else:
            fit += 1

print(fit)
