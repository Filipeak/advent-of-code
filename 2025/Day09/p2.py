with open("in.txt") as file:
    data = [list(map(lambda x: int(x), line.split(','))) for line in file.readlines()]


result = 0

for i in range(len(data)):
    for j in range(len(data)):
        if i != j:
            w = abs(data[i][0] - data[j][0]) + 1
            h = abs(data[i][1] - data[j][1]) + 1
            a = w * h

            for k in range(len(data)):
                p1 = data[k]
                p2 = data[(k + 1) % len(data)]

                xc1, xc2 = sorted([data[i][0], data[j][0]])
                xl1, xl2 = sorted([p1[0], p2[0]])
                yc1, yc2 = sorted([data[i][1], data[j][1]])
                yl1, yl2 = sorted([p1[1], p2[1]])

                if xl2 > xc1 and xl1 < xc2 and yl2 > yc1 and yl1 < yc2:
                    break
            else:
                if a > result:
                    result = a

print(result)
