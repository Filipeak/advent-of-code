with open("in_sample2.txt") as file:
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
        return (1, dac, fft)

    if current in cache:
        return cache[current]

    if current == "dac":
        dac = True

    if current == "fft":
        fft = True

    n = 0

    for o in graph[current]:
        (res, n_dac, n_fft) = trace_path(o, dac, fft)

        if n_dac and n_fft:
            n += res

    if n > 0:
        dac = True
        fft = True

    cache[current] = (n, dac, fft)

    return (n, dac, fft)

result = trace_path("svr", False, False)[0]
print(result)
