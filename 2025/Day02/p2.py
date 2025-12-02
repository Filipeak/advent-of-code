with open("in.txt") as f:
    data = list(map(lambda x: (int(x.split('-')[0]), int(x.split('-')[1])), f.read().split(',')))

result = 0

for low, high in data:
    for n in range(low, high + 1):
        s = str(n)
        l = len(s)

        for i in range(2, l + 1):
            if l % i == 0:
                div = l // i

                for j in range(1, i):
                    if s[div * (j - 1):div * j] != s[div * j:div * (j + 1)]:
                        break
                else:
                    result += n
                    break

print(result)
