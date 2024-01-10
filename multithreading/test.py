def prime_factorize(N):
    res = []

    for p in range(2, N):
        if p * p > N:
            break
        if N % p != 0:
            continue

        e = 0
        while N % p == 0:
            e += 1

            N //= p

        res.append((p, e))

    if N != 1:
        res.append((N, 1))

    return res

N = 1048576
pf = prime_factorize(N)

# 出力
print('{} = '.format(N), end='')
for (p, e) in pf:
    print('{}^{} '.format(p, e), end='')
print()
