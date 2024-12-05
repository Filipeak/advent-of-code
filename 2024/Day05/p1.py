from math import floor

with open("in.txt") as file:
    data = file.readlines()
    rules = {}
    updates = []
    setting_rules = True

    for line in data:
        if setting_rules:
            if line == "\n":
                setting_rules = False

                continue

            rule = list(map(lambda x: int(x), line.replace("\n", "").split("|")))
            key = rule[1]
            value = rule[0]

            if key in rules:
                rules[key].append(value)
            else:
                rules[key] = [value]
        else:
            updates.append(list(map(lambda x: int(x), line.replace("\n", "").split(","))))

s = 0

for update in updates:
    correct = True

    for i in range(len(update)):
        key = update[i]
        arr = update[0:i]

        if key in rules:
            for r in rules[key]:
                if r in update and r not in arr:
                    correct = False

                    break

        if not correct:
            break

    if correct:
        s += update[floor(len(update) / 2)]

print(s)
