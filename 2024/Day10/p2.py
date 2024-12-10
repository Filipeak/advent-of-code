with open("in.txt") as file:
    data = list(map(lambda x: x.replace("\n", ""), file.readlines()))
    xMax = len(data[0])
    yMax = len(data)


def _get_val(x, y):
    return int(data[y][x])


def calc_rating(x, y):
    n = _get_val(x, y)

    if n == 9:
        return 1

    rating = 0

    if x + 1 < xMax and _get_val(x + 1, y) == n + 1:
        rating += calc_rating(x + 1, y)
    if x - 1 >= 0 and _get_val(x - 1, y) == n + 1:
        rating += calc_rating(x - 1, y)
    if y + 1 < yMax and _get_val(x, y + 1) == n + 1:
        rating += calc_rating(x, y + 1)
    if y - 1 >= 0 and _get_val(x, y - 1) == n + 1:
        rating += calc_rating(x, y - 1)

    return rating


total_rating = 0

for i in range(len(data)):
    for j in range(len(data[i])):
        if _get_val(j, i) == 0:
            total_rating += calc_rating(j, i)

print(total_rating)
