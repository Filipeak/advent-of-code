import sympy

with open("in.txt") as file:
    data = [tuple(map(int, line.replace(' ', '').replace('@', ',').replace('\n', '').split(','))) for line in file.readlines()]

x_i, y_i, z_i, v_xi, v_yi, v_zi = sympy.symbols("x_i, y_i, z_i, v_xi, v_yi, v_zi")

eqs = []

for x_0, y_0, z_0, v_x0, v_y0, v_z0 in data:
    eq_l = (y_0 - y_i) * (v_xi - v_x0) - (x_0 - x_i) * (v_yi - v_y0)
    eq_r = (z_0 - z_i) * (v_xi - v_x0) - (x_0 - x_i) * (v_zi - v_z0)

    eqs.append(eq_l)
    eqs.append(eq_r)

ans = sympy.solve(eqs)[0]
result = ans[x_i] + ans[y_i] + ans[z_i]

print(result)