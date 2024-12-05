with open("in.txt") as file:
    data = list(map(lambda x: list(map(lambda y: int(y), x.replace("\n", "").split(" "))), file.readlines()))

c = 0

for x in data:
    t = "none"

    for i in range(1, len(x)):
        if t == "none":
            if x[i - 1] - x[i] >= 1 and x[i - 1] - x[i] <= 3:
                t = "dec"
            elif x[i] - x[i - 1] >= 1 and x[i] - x[i - 1] <= 3:
                t = "inc"
            else:
                break
        elif t == "inc":
            if not (x[i] - x[i - 1] >= 1 and x[i] - x[i - 1] <= 3):
                break
        elif t == "dec":
            if not (x[i - 1] - x[i] >= 1 and x[i - 1] - x[i] <= 3):
                break

        if i == len(x) - 1:
            c += 1

print(c)
