import numpy as np
import itertools
from math import floor, ceil

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


def gauss_jordan(matrix):
    M = np.array(matrix, dtype=float).copy()

    rows, cols = M.shape
    pivot_row = 0

    for j in range(cols):
        if pivot_row >= rows:
            break

        col_slice = np.abs(M[pivot_row:, j])
        max_row_index = np.argmax(col_slice) + pivot_row

        if max_row_index != pivot_row:
            M[[pivot_row, max_row_index]] = M[[max_row_index, pivot_row]]

        if abs(M[pivot_row, j]) < 1e-10:
            continue

        M[pivot_row] = M[pivot_row] / M[pivot_row, j]

        for i in range(rows):
            if i != pivot_row:
                M[i] -= M[i, j] * M[pivot_row]

        pivot_row += 1

    return M


def get_opt_eq(M):
    pivots = []
    free_vars = []

    # Get free vars and pivot vars
    for j in range(M.shape[1] - 1):
        col = M[:, j]

        if 1 in col and sum(np.abs(col)) == 1:
            pivots.append(j)
        else:
            free_vars.append(j)

    vars_eqs = []
    current_rhs = np.zeros(M.shape[1])

    # Calculate equations for pivot vars, add all of them to one sum equation
    for i in range(len(pivots)):
        rhs = [M[i, -1]]

        for j in range(M.shape[1] - 1):
            if pivots[i] == j:
                rhs.append(0)
            else:
                rhs.append(-M[i, j])

        vars_eqs.append((pivots[i], rhs))
        current_rhs += np.array(rhs)

    # Correct our sum equation by free vars
    for i in range(len(free_vars)):
        rhs = np.zeros(M.shape[1])
        rhs[1 + free_vars[i]] = 1

        current_rhs += rhs

    return free_vars, vars_eqs, current_rhs


def solve_eq(A, y):
    m_y = np.transpose([y])
    M = np.hstack((A, m_y))

    M = gauss_jordan(M)
    free_vars, vars_eqs, eq = get_opt_eq(M)

    possible_values = range(0, 200 + 1, 1)
    min_sum = 9999999

    # Brute force free vars
    for tmp_sol in itertools.product(possible_values, repeat=len(free_vars)):
        is_valid = True
        tmp_vars = []

        # Check if pivot vars are correct
        for e in vars_eqs:
            tmp_eq = e[1]
            res = tmp_eq[0]
            free_var_counter = 0

            for i in range(1, len(tmp_eq)):
                if i - 1 in free_vars:
                    res += tmp_eq[i] * tmp_sol[free_var_counter]
                    free_var_counter += 1

            if res < -1e-7 or not (abs(floor(res) - res) < 1e-7 or abs(ceil(res) - res) < 1e-7):
                is_valid = False
                break

            tmp_vars.append(res)

        # If so calculate sum and minimum
        if is_valid:
            res = eq[0]
            free_var_counter = 0

            for i in range(1, len(eq)):
                if i - 1 in free_vars:
                    res += eq[i] * tmp_sol[free_var_counter]
                    free_var_counter += 1

            res = round(res)
            min_sum = min(min_sum, res)

    return int(min_sum)


result = 0

for d in data:
    y = d[2]
    btns = d[1]
    v = [[1 if i in b else 0 for i, _ in enumerate(y)] for b in btns]
    v_T = [[v[j][i] for j in range(len(v))] for i in range(len(v[0]))]

    result += solve_eq(
        np.array(v_T).astype(float),
        np.array(y).astype(float)
    )

print(result)
