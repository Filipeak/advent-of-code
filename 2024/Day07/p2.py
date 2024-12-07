with open("in.txt") as file:
    data = file.readlines()
    eqs = []

    for line in data:
        tmp = [0, []]
        raw = line.replace("\n", "").split(":")
        tmp[0] = int(raw[0])
        tmp[1] = list(map(lambda x: int(x), raw[1].split(" ")[1:]))
        eqs.append(tmp)


def gen_ops(n):
    if n <= 0:
        return []
    elif n == 1:
        return ["+", "*", "|"]

    ops = gen_ops(n - 1)
    total = []

    for x in ops:
        total.append("+" + x)
        total.append("*" + x)
        total.append("|" + x)

    return total


cache = {}
s = 0

for x in eqs:
    val = x[0]
    nums = x[1]

    key = len(nums) - 1

    if key not in cache:
        cache[key] = gen_ops(key)

    for op in cache[key]:
        newOp = "+" + op
        total = 0

        for i in range(len(newOp)):
            if newOp[i] == "+":
                total += nums[i]
            elif newOp[i] == "*":
                total *= nums[i]
            elif newOp[i] == "|":
                total = int(str(total) + str(nums[i]))

        if total == val:
            s += val
            break


print(s)
