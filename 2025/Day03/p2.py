with open("in.txt") as f:
    data = list(map(lambda x: x.strip(), f.readlines()))

result = 0

for line in data:
    numbers = []
    current_idx = 0

    for k in range(12 - 1, -1, -1):
        max_number = -1
        max_number_idx = -1

        for i in range(current_idx, len(line) - k):
            n = int(line[i])

            if n > max_number:
                max_number = n
                max_number_idx = i

        numbers.append(str(max_number))
        current_idx = max_number_idx + 1

    result += int("".join(numbers))

print(result)
