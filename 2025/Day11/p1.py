with open("in.txt") as file:
    data = file.readlines()
    graph = {}

    for line in data:
        tmp = line.replace("\n", "").split(":")
        k = tmp[0]
        outputs = list(filter(lambda x: x != "", tmp[1].split(" ")))
        graph[k] = outputs


def trace_path(current):
    if current == "out":
        return 1

    n = 0

    for o in graph[current]:
        n += trace_path(o)

    return n


result = trace_path("you")
print(result)
