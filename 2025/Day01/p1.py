with open("in.txt") as f:
    data = list(map(lambda x: (x[0], int(x[1:])), f.readlines()))

pos = 50
n = 0

for dir, val in data:
    val = val if dir == 'R' else -val
    pos = (pos + val) % 100

    if pos == 0:
        n += 1

print(n)
