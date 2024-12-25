with open("in.txt") as file:
    lines = file.readlines()
    wires = {}
    ops = {}
    setting_wires = True

    for line in lines:
        if line == "\n":
            setting_wires = False
            continue

        if setting_wires:
            wire, value = line.strip().split(": ")
            wires[wire] = int(value)
        else:
            tokens = line.strip().replace("-> ", "").split(" ")
            ops[tokens[3]] = [tokens[1], tokens[0], tokens[2], False]

            if tokens[0] not in wires:
                wires[tokens[0]] = None
            if tokens[2] not in wires:
                wires[tokens[2]] = None
            if tokens[3] not in wires:
                wires[tokens[3]] = None


def process_gate(op):
    gate = ops[op]

    if gate[3]:
        return
    else:
        gate[3] = True

    gateType = gate[0]
    in1 = wires[gate[1]]
    in2 = wires[gate[2]]
    v = None

    if in1 is None:
        process_gate(gate[1])
        in1 = wires[gate[1]]
    if in2 is None:
        process_gate(gate[2])
        in2 = wires[gate[2]]

    if gateType == "AND":
        if in1 == 1 and in2 == 1:
            v = 1
        elif in1 == 0 or in2 == 0:
            v = 0
    elif gateType == "OR":
        if in1 == 1 or in2 == 1:
            v = 1
        elif in1 == 0 and in2 == 0:
            v = 0
    elif gateType == "XOR":
        if in1 != in2:
            v = 1
        else:
            v = 0

    wires[op] = v


for op in ops.keys():
    process_gate(op)

result = 0
n = 0

for wire in sorted(wires.keys()):
    if wire[0] == "z":
        result |= wires[wire] << n
        n += 1

print(result)
