n = int(input("Введите число: "))

if n < 2 or n > 10e9:
    print("Некорректный ввод")
    quit ()

s = 0
for i in range(1, n + 1):
    if n % i == 0: # получаю остаток от деления на i
        s = s + 1

if s == 2:
    print("Простое")
else:
    print("Составное")
