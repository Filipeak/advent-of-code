from collections import deque

with open("in.txt") as file:
    data = file.readlines()
    secret_numbers = [int(x) for x in data]


def evolve_number(n):
    def mix(a):
        nonlocal n
        n = a ^ n

    def prune():
        nonlocal n
        n = n % (1 << 24)

    n1 = n << 6
    mix(n1)
    prune()

    n2 = n >> 5
    mix(n2)
    prune()

    n3 = n << 11
    mix(n3)
    prune()

    return n


seqs = {}

for num in secret_numbers:
    cur_secret = num
    cur_count = cur_secret % 10

    last = deque()
    seen = set()

    for i in range(2000):
        cur_secret = evolve_number(cur_secret)
        new_count = cur_secret % 10
        diff = new_count - cur_count
        cur_count = new_count

        last.append(diff)
        if len(last) >= 5:
            last.popleft()

        if len(last) == 4:
            key = tuple(last)

            if key in seen:
                continue

            seen.add(key)

            if key in seqs:
                seqs[key] += cur_count
            else:
                seqs[key] = cur_count

print(max(seqs.values()))
