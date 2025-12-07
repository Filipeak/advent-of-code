with open("in.txt") as file:
    data = file.readlines()
    start_pos = (0, data[0].index("S"))


cache = {}


def count_path(pos):
    if pos[0] == len(data) - 1:
        return 1

    if pos in cache:
        return cache[pos]

    pos = (pos[0] + 1, pos[1])

    if data[pos[0]][pos[1]] == '^':
        left_pos = (pos[0], pos[1] - 1)
        right_pos = (pos[0], pos[1] + 1)

        v = count_path(left_pos) + count_path(right_pos)
        cache[pos] = v
        return v
    else:
        v = count_path(pos)
        cache[pos] = v
        return v


print(count_path(start_pos))
