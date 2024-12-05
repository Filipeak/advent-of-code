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
            key = rule[0]
            value = rule[1]

            if key in rules:
                rules[key].append(value)
            else:
                rules[key] = [value]
        else:
            updates.append(list(map(lambda x: int(x), line.replace("\n", "").split(","))))

s = 0

for update in updates:
    correct = True
    counts = {}

    for i in range(len(update)):
        key = update[i]
        rule = [] if key not in rules else list(filter(lambda x: x in update, rules[key]))
        counts[key] = len(rule)

    updatesCounts = list(counts.keys())
    newCounts = {k: v for k, v in sorted(counts.items(), key=lambda item: item[1], reverse=True)}
    newCounts = list(newCounts.keys())

    if newCounts != updatesCounts:
        s += newCounts[floor(len(newCounts) / 2)]

print(s)
