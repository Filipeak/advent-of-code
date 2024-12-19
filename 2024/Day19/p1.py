with open("in.txt") as file:
    lines = file.readlines()
    patterns = [x for x in lines[0].strip().split(", ")]
    designs = []

    for i in range(2, len(lines)):
        designs.append(lines[i].strip())


cache = {}


def is_valid(design):
    if len(design) == 0:
        return True

    if design in cache:
        return cache[design]

    for i in range(len(design)):
        s = design[:i+1]

        if s in patterns:
            if is_valid(design[i+1:]):
                cache[design] = True

                return True

    cache[design] = False

    return False


count = 0
for des in designs:
    if is_valid(des):
        count += 1
print(count)
