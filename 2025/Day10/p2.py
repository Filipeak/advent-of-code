from ortools.sat.python import cp_model

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


result = 0

for d in data:
    y = d[2]
    btns = d[1]
    v = [[1 if i in b else 0 for i, x in enumerate(y)] for b in btns]

    model = cp_model.CpModel()
    xs = [model.NewIntVar(0, 1000, f'x{i}') for i in range(len(v))]

    for dim in range(len(y)):
        model.add(sum([xs[i] * v[i][dim] for i in range(len(v))]) == y[dim])

    model.minimize(sum(xs))

    solver = cp_model.CpSolver()
    res = solver.Solve(model)

    if res in (cp_model.OPTIMAL, cp_model.FEASIBLE):
        result += sum([int(solver.Value(x)) for x in xs])

print(result)
