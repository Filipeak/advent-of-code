import itertools

with open("in.txt") as file:
    lines = file.readlines()
    data = []

    for line in lines:
        tmp = line.replace("\n", "").split(" ")
        code = tmp[0][1:-1]
        buttons = []

        for btn in tmp[1:-1]:
            buttons.append([int(b) for b in btn[1:-1].split(',')])

        joltage = tmp[-1][1:-1]

        data.append((code, buttons, joltage))


result = 0

for d in data:
    desired_state = list(map(lambda x: 0 if x == '.' else 1, d[0]))
    btns = d[1]
    min_len = 99999

    for i in range(1, len(btns) + 1):
        for comb in itertools.combinations(btns, i):
            btn_counts = {}

            for current in comb:
                for id in current:
                    if id in btn_counts:
                        btn_counts[id] += 1
                    else:
                        btn_counts[id] = 1
            
            for i in range(len(desired_state)):
                if i not in btn_counts:
                    btn_counts[i] = 0
                
                if btn_counts[i] % 2 != desired_state[i]:
                    break
            else:
                min_len = min(min_len, len(comb))
    
    result += min_len

print(result)