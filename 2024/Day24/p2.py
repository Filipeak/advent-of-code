# MADE WITH HELP: https://www.reddit.com/r/adventofcode/comments/1hla5ql/2024_day_24_part_2_a_guide_on_the_idea_behind_the/

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
            ops[tokens[3]] = [tokens[1], tokens[0], tokens[2]]

            if tokens[0] not in wires:
                wires[tokens[0]] = None
            if tokens[2] not in wires:
                wires[tokens[2]] = None
            if tokens[3] not in wires:
                wires[tokens[3]] = None


swaps = []


def swap(op1, op2):
    tmp = ops[op1]
    ops[op1] = ops[op2]
    ops[op2] = tmp

    swaps.append(op1)
    swaps.append(op2)


# Find 6 which don't meet the 2 rules

rule1 = []
rule2 = []

for op in ops:
    if op[0] == 'z' and ops[op][0] != "XOR" and op != sorted(ops.keys())[-1]:
        rule1.append(op)
    if op[0] != 'z' and ops[op][1][0] not in "xy" and ops[op][2][0] not in "xy" and ops[op][0] == "XOR":
        rule2.append(op)


# Find pairings for those 6

def find_next_pairing(op):
    if op[0] == 'z':
        return int(op[1:3])

    m = float('inf')
    for o in ops:
        if ops[o][1] == op or ops[o][2] == op:
            tmp = find_next_pairing(o)

            if tmp < m:
                m = tmp
    return m


for a in rule2:
    n = find_next_pairing(a) - 1
    z = "z" + str(n)

    swap(a, z)


# Do the analysis for the remaining 2

def process_gate(op):
    gate = ops[op]

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

results = {"x": [0, 0], "y": [0, 0], "z": [0, 0]}

for wire in sorted(wires.keys()):
    if wire[0] == "x":
        results['x'][0] |= wires[wire] << results['x'][1]
        results['x'][1] += 1
    if wire[0] == "y":
        results['y'][0] |= wires[wire] << results['y'][1]
        results['y'][1] += 1
    if wire[0] == "z":
        results['z'][0] |= wires[wire] << results['z'][1]
        results['z'][1] += 1

strX = "0{:b}".format(results['x'][0])
strY = "0{:b}".format(results['y'][0])
strZ = "{:b}".format(results['z'][0])
strXY = "{:b}".format(results['x'][0] + results['y'][0])


# XOR actual with desired to find bits which are messed up

print("{:b}".format(results['z'][0] ^ (results['x'][0] + results['y'][0])))


# Find that "svm" has AND, and "nbc" has XOR with the same inputs. Swap them.

swap("nbc", "svm")


print(",".join(sorted(swaps)))
