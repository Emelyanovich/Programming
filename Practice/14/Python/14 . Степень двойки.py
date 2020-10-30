x = int(input("Введите число: "))

if x < 0 or x > 10e15:
    print("Некорректный ввод")
    quit()

s = 0
if x != 0:
    n = 1
    while n <= x:
        n *= 2
        s += 1

print (s)
