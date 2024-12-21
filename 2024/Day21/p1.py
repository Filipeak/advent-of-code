from collections import deque
from itertools import product

with open("in.txt") as file:
    lines = [x.replace("\n", "") for x in file.readlines()]


def generate_numpads(code, btns):
    pos_map = {}
    for i in range(len(btns)):
        for j in range(len(btns[i])):
            pos_map[btns[i][j]] = (i, j)

    current = pos_map['A']
    total = []

    for seq in code:
        new_pos = pos_map[seq]
        possibilities = []
        q = deque([(current[0], current[1], [])])
        least_moves = float('inf')

        while q:
            r, c, moves = q.popleft()

            for nr, nc in [(r, c+1), (r, c-1), (r+1, c), (r-1, c)]:
                if 0 <= nr < len(btns) and 0 <= nc < len(btns[0]):
                    if (nr, nc) == pos_map[' ']:
                        continue
                    if (nr, nc) in moves:
                        continue

                    nmoves = moves + [(r, c)]

                    if (nr, nc) == new_pos:
                        if len(moves) + 1 > least_moves:
                            continue

                        least_moves = len(moves) + 1
                        possibilities.append(nmoves + [(nr, nc)])
                    else:
                        q.append((nr, nc, nmoves))

        if len(possibilities) > 0:
            dirs = []
            for poss in possibilities:
                tmpD = ""
                for i in range(1, len(poss)):
                    d = (poss[i][1] - poss[i-1][1], poss[i][0] - poss[i-1][0])
                    tmpD += {(1, 0): ">", (0, 1): "v", (-1, 0): "<", (0, -1): "^"}[d]
                dirs.append(tmpD + "A")

            total.append(dirs)
        else:
            total.append(["A"])

        current = new_pos

    return ["".join(x) for x in product(*total)]


numeric_grid = [
    ['7', '8', '9'],
    ['4', '5', '6'],
    ['1', '2', '3'],
    [' ', '0', 'A'],
]
directional_grid = [
    [' ', '^', 'A'],
    ['<', 'v', '>'],
]
complexity = 0

for code in lines:
    g1 = generate_numpads(code, numeric_grid)

    g2 = []
    for g in g1:
        g2 += generate_numpads(g, directional_grid)

    m = float("inf")
    for g in g2:
        tmp = list(map(len, generate_numpads(g, directional_grid)))
        m = min(m, min(tmp))

    num = int(code.replace("A", ""))
    complexity += num * m

print(complexity)
