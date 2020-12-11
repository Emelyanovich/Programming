def factorization(number):
    p = {}
    i = 2
    while i * i <= number:
        while number % i == 0:
            p[i] = p.get(i,0) + 1
            number //= i
        i += 1
    if number > 1:
        if number not in p :
            p[number] = p.get(number,1)
    return p
 
 
number = int(input())
p = factorization(number)
fdict = sorted(list(p.keys()))
res = ''
for i in fdict :
    res += str(i) + '^' + str(p[i]) + '*'
print(res[:-1])
