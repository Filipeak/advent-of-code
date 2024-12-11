with open("in.txt") as file:
    nums = list(map(lambda x: int(x), file.readline().replace("\n", "").split(" ")))


def calculate(inp, depth, memo):
    if depth == 75:
        return len(inp)

    total = 0

    for x in inp:
        key = (x, depth)
        if key in memo:
            total += memo[key]
            continue

        data = []

        if x == 0:
            data.append(1)
        elif len(str(x)) % 2 == 0:
            s = str(x)
            data.append(int(s[:int(len(s) / 2)]))
            data.append(int(s[int(len(s) / 2):]))
        else:
            data.append(x * 2024)

        value = calculate(data, depth + 1, memo)
        memo[(x, depth)] = value

        total += value

    return total


print(calculate(nums, 0, {}))
