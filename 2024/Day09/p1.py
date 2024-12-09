with open("in.txt") as file:
    data = file.readline().replace("\n", "")

freeSpace = False
currentId = 0
s = []

for i in range(len(data)):
    for j in range(int(data[i])):
        s.append(str(currentId) if not freeSpace else ".")

    if freeSpace:
        currentId += 1

    freeSpace = not freeSpace

lastIndex = len(s) - 1

for i in range(len(s)):
    if s[i] == ".":
        if s[lastIndex] == ".":
            for j in range(lastIndex):
                ind = lastIndex - j - 1

                if s[ind] != ".":
                    lastIndex = ind

                    break

        if i > lastIndex:
            break

        s[i] = s[lastIndex]
        s[lastIndex] = "."

checksum = 0

for i in range(len(s)):
    if s[i] == ".":
        break

    checksum += i * int(s[i])

print(checksum)
