with open("in.txt") as f:
    data = list(map(lambda x: (int(x.split('-')[0]), int(x.split('-')[1])), f.read().split(',')))

result = 0

for low, high in data:
    for n in range(low, high + 1):
        s = str(n)
        l = len(s)

        if l % 2 == 0:
            if s[:l // 2] == s[l // 2:]:
                result += n

print(result)
