A, act, B = input("Введите арифметическое действие через пробел: ").split()
A = float(A)
B = float(B)

if act == "+":
    print(A + B)
elif act == "-":
    print(A - B)
elif act == "*":
    print(A * B)
elif act == "/":
    if B!=0:
        print(A / B)
    else:
        print("Деление на ноль")
else:
    print("В данной программе нет этого действия")

