with open("in.txt") as file:
    nums = list(map(lambda x: int(x), file.readline().replace("\n", "").split(" ")))

currentData = nums
nextData = []

for _ in range(25):
    nextData = []

    for x in currentData:
        if x == 0:
            nextData.append(1)
        elif len(str(x)) % 2 == 0:
            s = str(x)
            nextData.append(int(s[:int(len(s) / 2)]))
            nextData.append(int(s[int(len(s) / 2):]))
        else:
            nextData.append(x * 2024)

    currentData = nextData

print(len(nextData))
