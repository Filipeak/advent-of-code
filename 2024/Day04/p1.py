with open("in.txt") as file:
    data = list(map(lambda x: x.replace("\n", ""), file.readlines()))


WORD = "XMAS"


def search_for_word(row, col):
    DIRS_COUNT = 8
    errs = 0
    x = [1, 1, 0, -1, -1, -1, 0, 1]
    y = [0, -1, -1, -1, 0, 1, 1, 1]

    for dir in range(DIRS_COUNT):
        curX = col
        curY = row

        for k in range(len(WORD)):
            if curX < 0 or curX >= len(data[0]) or curY < 0 or curY >= len(data) or data[curY][curX] != WORD[k]:
                errs += 1
                break
            else:
                curX += x[dir]
                curY += y[dir]

    return DIRS_COUNT - errs


total = 0

for i in range(len(data)):
    for j in range(len(data[i])):
        if data[i][j] == "X":
            total += search_for_word(i, j)

print(total)
