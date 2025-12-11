with open("in.txt") as file:
    data = file.readlines()
    graph = {}

    for line in data:
        tmp = line.replace("\n", "").split(":")
        k = tmp[0]
        outputs = list(filter(lambda x: x != "", tmp[1].split(" ")))
        graph[k] = outputs


def trace_path(current, end, cache):
    if current == end:
        return 1

    if current not in graph:
        return 0
    
    if current in cache:
        return cache[current]

    n = 0

    for o in graph[current]:
        n += trace_path(o, end, cache)

    cache[current] = n

    return n


svr_dac = trace_path("svr", "dac", {})
svr_fft = trace_path("svr", "fft", {})
dac_fft = trace_path("dac", "fft", {})
fft_dac = trace_path("fft", "dac", {})
dac_out = trace_path("dac", "out", {})
fft_out = trace_path("fft", "out", {})

print(svr_dac * dac_fft * fft_out + svr_fft * fft_dac * dac_out)
