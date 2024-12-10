with open("in.txt") as file:
    data = list(map(lambda x: x.replace("\n", ""), file.readlines()))
    xMax = len(data[0])
    yMax = len(data)


def _get_val(x, y):
    return int(data[y][x])


def calc_score(x, y, cache):
    n = _get_val(x, y)

    if n == 9:
        if (x, y) in cache:
            return 0
        else:
            cache[(x, y)] = 1
            return 1

    score = 0

    if x + 1 < xMax and _get_val(x + 1, y) == n + 1:
        score += calc_score(x + 1, y, cache)
    if x - 1 >= 0 and _get_val(x - 1, y) == n + 1:
        score += calc_score(x - 1, y, cache)
    if y + 1 < yMax and _get_val(x, y + 1) == n + 1:
        score += calc_score(x, y + 1, cache)
    if y - 1 >= 0 and _get_val(x, y - 1) == n + 1:
        score += calc_score(x, y - 1, cache)

    return score

total_score = 0

for i in range(len(data)):
    for j in range(len(data[i])):
        if _get_val(j, i) == 0:
            total_score += calc_score(j, i, {})

print(total_score)
