size = int(input("Введите длину:"))
first = int(input("Первый элемент:"))
toplus = int(input("Шаг прогрессии:"))


def create(size, first=0, toplus=0):
    return [first + item * toplus for item in range(size)]


def sort(mass):
    for i in range(1, len(mass)):
        key = mass[i]
        j = i - 1
        while j >= 0 and key < mass[j]:
            mass[j + 1] = mass[j]
            j -= 1
        mass[j + 1] = key
    return mass


print(sort(create(size, first, toplus)))
