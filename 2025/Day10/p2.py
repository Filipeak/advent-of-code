with open("in.txt") as file:
    lines = file.readlines()
    data = []

    for line in lines:
        tmp = line.replace("\n", "").split(" ")
        code = tmp[0][1:-1]
        buttons = []

        for btn in tmp[1:-1]:
            buttons.append([int(b) for b in btn[1:-1].split(',')])

        joltage = list(map(lambda x: int(x), tmp[-1][1:-1].split(',')))

        data.append((code, buttons, joltage))


cache = {}


def solve(state, btns):
    if any([s < 0 for s in state]):
        return None

    if all([s == 0 for s in state]):
        return 0

    if tuple(state) in cache:
        return cache[tuple(state)]

    min_len = 99999

    for b in btns:
        tmp_state = state.copy()

        for id in b:
            tmp_state[id] -= 1

        res = solve(tmp_state, btns)

        if res is not None:
            min_len = min(min_len, 1 + res)

    cache[tuple(state)] = min_len

    return min_len


result = 0

for d in data:
    btns = d[1]
    joltage = d[2]

    cache = {}
    result += solve(joltage, btns)

print(result)
