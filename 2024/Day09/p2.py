with open("in.txt") as file:
    data = file.readline().replace("\n", "")

freeSpace = False
currentId = 0
s = []

for i in range(len(data)):
    s.append([str(currentId) if not freeSpace else "."] * int(data[i]))

    if freeSpace:
        currentId += 1

    freeSpace = not freeSpace

lastIndex = len(s) - 1

for i in range(len(s) - 1, -1, -1):
    if len(s[i]) > 0 and s[i][0] != ".":
        for j in range(i):
            if len(s[j]) > 0 and len(list(filter(lambda x: x == ".", s[j]))) >= len(s[i]):
                ind = 0

                for k in range(len(s[j])):
                    if s[j][k] != ".":
                        continue
                    if ind >= len(s[i]):
                        break

                    s[j][k] = s[i][ind]
                    s[i][ind] = None
                    ind += 1

                break

checksum = 0
pos = 0

for i in range(len(s)):
    for j in range(len(s[i])):
        if s[i][j] not in [".", None]:
            checksum += pos * int(s[i][j])
        pos += 1


print(checksum)
