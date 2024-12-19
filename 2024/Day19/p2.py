with open("in.txt") as file:
    lines = file.readlines()
    patterns = [x for x in lines[0].strip().split(", ")]
    designs = []

    for i in range(2, len(lines)):
        designs.append(lines[i].strip())


cache = {}


def count_possibilities(design):
    if len(design) == 0:
        return 1

    if design in cache:
        return cache[design]

    total_count = 0

    for i in range(len(design)):
        s = design[:i+1]

        if s in patterns:
            poss = count_possibilities(design[i+1:])
            total_count += poss

    cache[design] = total_count

    return total_count


count = 0
for des in designs:
    count += count_possibilities(des)
print(count)
