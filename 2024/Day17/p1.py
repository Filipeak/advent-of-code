with open("in.txt") as file:
    lines = file.readlines()

    reg_a = int(lines[0].split(": ")[1])
    reg_b = int(lines[1].split(": ")[1])
    reg_c = int(lines[2].split(": ")[1])
    instructions = [int(x) for x in lines[4].split(": ")[1].split(",")]

pointer = 0
out_buff = []


def combo_op(op):
    if op >= 0 and op <= 3:
        return op
    elif op == 4:
        return reg_a
    elif op == 5:
        return reg_b
    elif op == 6:
        return reg_c
    else:
        raise "ERR"


while pointer < len(instructions):
    opcode = instructions[pointer]
    operand = instructions[pointer + 1]

    if opcode == 0:
        reg_a = int(reg_a / (2 ** combo_op(operand)))
        pointer += 2
    elif opcode == 1:
        reg_b = reg_b ^ operand
        pointer += 2
    elif opcode == 2:
        reg_b = combo_op(operand) % 8
        pointer += 2
    elif opcode == 3:
        if reg_a != 0:
            pointer = operand
        else:
            pointer += 2
    elif opcode == 4:
        reg_b = reg_b ^ reg_c
        pointer += 2
    elif opcode == 5:
        val = combo_op(operand) % 8
        out_buff.append(str(val))
        pointer += 2
    elif opcode == 6:
        reg_b = int(reg_a / (2 ** combo_op(operand)))
        pointer += 2
    elif opcode == 7:
        reg_c = int(reg_a / (2 ** combo_op(operand)))
        pointer += 2
    else:
        raise "ERR"

print(",".join(out_buff))
