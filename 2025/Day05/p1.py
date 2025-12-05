with open("in.txt") as file:
    data = list(map(lambda x: x.replace("\n", ""), file.readlines()))

    switch = False
    ranges = []
    ingredients = []

    for line in data:
        if line == "":
            switch = True
            continue

        if not switch:
            tmp = line.split("-")
            ranges.append((int(tmp[0]), int(tmp[1])))
        else:
            ingredients.append(int(line))

result = 0

for ing in ingredients:
    for r in ranges:
        if ing >= r[0] and ing <= r[1]:
            result += 1
            break

print(result)
