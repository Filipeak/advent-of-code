with open("in.txt") as file:
    lines = list(map(lambda x: x.replace("\n", ""), file.readlines()))
    numbers = []
    ops = []

    for col in range(len(lines[0])):
        n = 0
        op = None

        for row in range(len(lines)):
            if lines[row][col] in ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]:
                n = n * 10 + int(lines[row][col])
            elif lines[row][col] in ["*", "+"]:
                op = lines[row][col]

        if op is not None:
            ops.append(op)
            numbers.append([])

        if n != 0:
            numbers[-1].append(n)


result = 0

for i in range(len(ops)):
    add = ops[i] == '+'
    tmp_result = 0 if add else 1

    for num in numbers[i]:
        if add:
            tmp_result += num
        else:
            tmp_result *= num

    result += tmp_result

print(result)
