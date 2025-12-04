with open("in.txt") as file:
    data = list(map(lambda x: x.strip(), file.readlines()))

result = 0

for r in range(len(data)):
    for c in range(len(data[r])):
        if data[r][c] != '@':
            continue

        count = 0

        for dir in [(-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1)]:
            if r + dir[0] >= 0 and r + dir[0] < len(data) and c + dir[1] >= 0 and c + dir[1] < len(data[r]) and data[r + dir[0]][c + dir[1]] == '@':
                count += 1

        if count < 4:
            result += 1

print(result)
