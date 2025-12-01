with open("in.txt") as f:
    data = list(map(lambda x: (x[0], int(x[1:])), f.readlines()))

pos = 50
n = 0

for dir, val in data:
    rotations = val // 100
    n += rotations
    val %= 100

    val = val if dir == 'R' else -val

    if pos != 0 and (pos + val <= 0 or pos + val >= 100):
        n += 1

    pos = (pos + val) % 100

print(n)
