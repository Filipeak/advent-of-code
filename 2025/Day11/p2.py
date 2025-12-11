with open("in.txt") as file:
    data = file.readlines()
    graph = {}

    for line in data:
        tmp = line.replace("\n", "").split(":")
        k = tmp[0]
        outputs = list(filter(lambda x: x != "", tmp[1].split(" ")))
        graph[k] = outputs


cache = {}


def trace_path(current, dac, fft):
    if current == "out":
        return 1 if dac and fft else 0

    key = (current, dac, fft)

    if key in cache:
        return cache[key]

    if current == "dac":
        dac = True

    if current == "fft":
        fft = True

    n = 0

    for o in graph[current]:
        n += trace_path(o, dac, fft)

    cache[key] = n

    return n


result = trace_path("svr", False, False)
print(result)
