with open("in.txt") as file:
    data = file.readlines()
    start_pos = (0, data[0].index("S"))

positions = [start_pos]
split_count = 0

while positions[0][0] < len(data) - 1:
    new_positions = []

    for i in range(len(positions)):
        positions[i] = (positions[i][0] + 1, positions[i][1])

        if data[positions[i][0]][positions[i][1]] == '^':
            current_pos = (positions[i][0], positions[i][1])

            positions[i] = (current_pos[0], current_pos[1] - 1)

            new_positions.append((current_pos[0], current_pos[1] + 1))
            split_count += 1

    positions.extend(new_positions)
    positions = list(set(positions))


print(split_count)
