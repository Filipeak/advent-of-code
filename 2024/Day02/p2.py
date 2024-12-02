with open("in.txt") as file:
    data = list(map(lambda x: list(map(lambda y: int(y), x.replace("\n", "").split(" "))), file.readlines()))

c = 0

for x in data:
    valid = False
    ignoreIndex = -1

    def get_previous_element(ind):
        if ind - 1 == ignoreIndex:
            return x[ind - 2]
        else:
            return x[ind - 1]

    for j in range(len(x) + 1):
        t = "none"

        for i in range(len(x)):
            if i == 0 or i == ignoreIndex or (i == 1 and ignoreIndex == 0):
                continue

            if t == "none":
                if get_previous_element(i) - x[i] >= 1 and get_previous_element(i) - x[i] <= 3:
                    t = "dec"
                elif x[i] - get_previous_element(i) >= 1 and x[i] - get_previous_element(i) <= 3:
                    t = "inc"
                else:
                    break
            elif t == "inc":
                if not (x[i] - get_previous_element(i) >= 1 and x[i] - get_previous_element(i) <= 3):
                    break
            elif t == "dec":
                if not (get_previous_element(i) - x[i] >= 1 and get_previous_element(i) - x[i] <= 3):
                    break

            if i == len(x) - 1 or (ignoreIndex == len(x) - 1 and i == len(x) - 2):
                valid = True

                break
        
        ignoreIndex = j

        if valid:
            c += 1

            break

print(c)