with open("in.txt") as file:
    lines = file.readlines()

    reg_a = int(lines[0].split(": ")[1])
    reg_b = int(lines[1].split(": ")[1])
    reg_c = int(lines[2].split(": ")[1])
    instructions = [int(x) for x in lines[4].split(": ")[1].split(",")]
    ins_str = ",".join(list(map(lambda x: str(x), instructions)))


def calc_for_a(a):
    r_a = a
    r_b = reg_b
    r_c = reg_c
    pointer = 0
    out_buff = []

    def combo_op(op):
        if op >= 0 and op <= 3:
            return op
        elif op == 4:
            return r_a
        elif op == 5:
            return r_b
        elif op == 6:
            return r_c
        else:
            raise "ERR"

    while pointer < len(instructions):
        opcode = instructions[pointer]
        operand = instructions[pointer + 1]

        if opcode == 0:
            r_a = int(r_a / (2 ** combo_op(operand)))
            pointer += 2
        elif opcode == 1:
            r_b = r_b ^ operand
            pointer += 2
        elif opcode == 2:
            r_b = combo_op(operand) % 8
            pointer += 2
        elif opcode == 3:
            if r_a != 0:
                pointer = operand
            else:
                pointer += 2
        elif opcode == 4:
            r_b = r_b ^ r_c
            pointer += 2
        elif opcode == 5:
            val = combo_op(operand) % 8
            out_buff.append(str(val))
            pointer += 2
        elif opcode == 6:
            r_b = int(r_a / (2 ** combo_op(operand)))
            pointer += 2
        elif opcode == 7:
            r_c = int(r_a / (2 ** combo_op(operand)))
            pointer += 2
        else:
            raise "ERR"

    return out_buff


n = 0

for i in range(len(instructions) - 1, -1, -1):
    for j in range(8):
        potentialN = n << 3 | j
        v = int(calc_for_a(potentialN)[0])

        if instructions[i] == v:
            n = potentialN
            break

print(n)
