with open("in.txt") as file:
    nums = []
    ops = []

    for line in file.readlines():
        tmp_nums = []

        for s in line.split(" "):
            if s != "" and s != "\n":
                if s in ["*", "+"]:
                    ops.append(s)
                else:
                    tmp_nums.append(int(s))

        if len(tmp_nums) > 0:
            nums.append(tmp_nums)


result = 0

for j in range(len(nums[0])):
    add = ops[j] == '+'
    tmp_result = 0 if add else 1

    for i in range(len(nums)):
        if add:
            tmp_result += nums[i][j]
        else:
            tmp_result *= nums[i][j]

    result += tmp_result

print(result)
