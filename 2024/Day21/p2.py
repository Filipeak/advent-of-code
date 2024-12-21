# MADE WITH HELP: https://www.youtube.com/watch?v=dqzAaj589cM

from collections import deque
from itertools import product
from functools import cache

with open("in.txt") as file:
    lines = [x.replace("\n", "") for x in file.readlines()]


def compute_path_for_grid(grid):
    pos_map = {}
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            pos_map[grid[i][j]] = (i, j)

    paths = {}
    for x in pos_map:
        for y in pos_map:
            if x == ' ' or y == ' ':
                continue

            possibilities = []
            q = deque([(pos_map[x][0], pos_map[x][1], [])])
            least_moves = float('inf')

            while q:
                r, c, moves = q.popleft()

                for nr, nc in [(r, c+1), (r, c-1), (r+1, c), (r-1, c)]:
                    if 0 <= nr < len(grid) and 0 <= nc < len(grid[0]):
                        if (nr, nc) == pos_map[' ']:
                            continue
                        if (nr, nc) in moves:
                            continue

                        nmoves = moves + [(r, c)]

                        if grid[nr][nc] == y:
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

                paths[(x, y)] = dirs
            else:
                paths[(x, y)] = ["A"]

    return paths


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
numeric_paths = compute_path_for_grid(numeric_grid)
directional_paths = compute_path_for_grid(directional_grid)


@cache
def solve(seq, depth=25):
    if depth == 1:
        return sum(len(directional_paths[(x, y)][0]) for x, y in zip("A" + seq, seq))

    length = 0

    for x, y in zip("A" + seq, seq):
        minlen = float('inf')

        for sub in directional_paths[(x, y)]:
            tmp = solve(sub, depth - 1)

            if tmp < minlen:
                minlen = tmp

        length += minlen

    return length


def generate_keypads(code, paths):
    options = []

    for seq in zip("A" + code, code):
        options.append(paths[seq])

    return ["".join(x) for x in product(*options)]


complexity = 0

for code in lines:
    ins = generate_keypads(code, numeric_paths)
    optimal = min([solve(seq) for seq in ins])

    num = int(code.replace("A", ""))
    complexity += num * optimal

print(complexity)
