with open("in.txt") as file:
    connections = [line.strip().split('-') for line in file.readlines()]

connections_map = {}

for pair in connections:
    if pair[0] not in connections_map:
        connections_map[pair[0]] = [pair[1]]
    else:
        connections_map[pair[0]].append(pair[1])

    if pair[1] not in connections_map:
        connections_map[pair[1]] = [pair[0]]
    else:
        connections_map[pair[1]].append(pair[0])

groups = set()

for main in connections_map:
    current_connections = connections_map[main]
    cons = {}

    for i in range(len(current_connections)):
        shared = [main, current_connections[i]]

        for j in range(len(current_connections)):
            if i != j:
                if current_connections[i] in connections_map[current_connections[j]]:
                    shared.append(current_connections[j])

        shared = tuple(sorted(shared))

        if shared in cons:
            cons[shared] += 1
        else:
            cons[shared] = 1

    for key in cons:
        if cons[key] == len(key) - 1:
            groups.add(key)

curr = None

for group in groups:
    if curr is None or len(group) > len(curr):
        curr = group

print(",".join(curr))
