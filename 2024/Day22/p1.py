with open("in.txt") as file:
    data = file.readlines()
    secret_numbers = [int(x) for x in data]


def evolve_number(n):
    def mix(a):
        nonlocal n
        n = a ^ n

    def prune():
        nonlocal n
        n = n % 16777216

    n1 = n * 64
    mix(n1)
    prune()

    n2 = n // 32
    mix(n2)
    prune()

    n3 = n * 2048
    mix(n3)
    prune()

    return n

s = 0
for num in secret_numbers:
    x = num
    for i in range(2000):
        x = evolve_number(x)
    s += x
print(s)