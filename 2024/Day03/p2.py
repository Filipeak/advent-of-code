with open("in.txt") as file:
    data = file.readlines()
    data = "".join(data)
    muls = data.split("mul")

enabled = True
s = 0

for x in muls:
    if x[0] != "(":
        do_ind = x.rfind("do()")
        dont_ind = x.rfind("don't()")

        if do_ind > dont_ind:
            enabled = True
        elif do_ind < dont_ind:
            enabled = False

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

    if enabled and end and a_set and b_set:
        s += a * b

    do_ind = x.rfind("do()")
    dont_ind = x.rfind("don't()")

    if do_ind > dont_ind:
        enabled = True
    elif do_ind < dont_ind:
        enabled = False

print(s)
