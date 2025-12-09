with open("in.txt") as file:
    data = [list(map(lambda x: int(x), line.split(','))) for line in file.readlines()]


result = 0

for i in range(len(data)):
    for j in range(len(data)):
        if i != j:
            w = abs(data[i][0] - data[j][0]) + 1
            h = abs(data[i][1] - data[j][1]) + 1
            a = w * h

            result = max(result, a)

print(result)
