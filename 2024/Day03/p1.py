with open("in.txt") as file:
    data = file.readlines()
    data = "".join(data)
    muls = data.split("mul")

s = 0

for x in muls:
    if x[0] != "(":
        continue

    end = False
    switched = False
    a = 0
    b = 0
    a_set = False
    b_set = False

    for i in range(1, len(x)):
        if x[i] in ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]:
            if not switched:
                a = 10 * a + int(x[i])
                a_set = True
            else:
                b = 10 * b + int(x[i])
                b_set = True
        elif x[i] == ",":
            if switched:
                break

            switched = True
        elif x[i] == ")":
            end = True
            
            break
        else:
            break

    if end and a_set and b_set:
        s += a * b

print(s)
