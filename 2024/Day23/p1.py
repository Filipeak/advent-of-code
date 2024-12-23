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

    for i in range(len(current_connections)):
        for j in range(len(current_connections)):
            if i != j:
                if current_connections[i] in connections_map[current_connections[j]]:
                    groups.add(tuple(sorted([main, current_connections[i], current_connections[j]])))

print(len(list(filter(lambda x: any([y[0] == 't' for y in x]), groups))))
