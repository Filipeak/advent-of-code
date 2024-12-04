with open("in.txt") as file:
    data = list(map(lambda x: x.replace("\n", ""), file.readlines()))


def check_X(row, col):
    if row >= 1 and row <= len(data) - 2 and col >= 1 and col <= len(data[0]) - 2:
        return (
            (data[row - 1][col - 1] == "M" and data[row + 1][col + 1] == "S")
            or (data[row - 1][col - 1] == "S" and data[row + 1][col + 1] == "M")
        ) and (
            (data[row - 1][col + 1] == "M" and data[row + 1][col - 1] == "S")
            or (data[row - 1][col + 1] == "S" and data[row + 1][col - 1] == "M")
        )
    
    return False


total = 0

for i in range(len(data)):
    for j in range(len(data[i])):
        if data[i][j] == "A":
            if check_X(i, j):
                total += 1

print(total)
