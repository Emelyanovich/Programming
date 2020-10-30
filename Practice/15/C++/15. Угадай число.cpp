#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");

    int g, n, s, x;

    g = 1;
    while (g == 1) {
        n = rand() % 100;
        cout << "Привет! Угадай число до 100, которое загадал компьютер. ";

        s = 0;
        while (true) {
            s++;
            cin >> x;
            if (x == n) {
                cout << "Поздравляю! Вы угадали" << endl;
                break;
            }
            else if (x > n)
                cout << "Загаданное число меньше" << endl;
            else
                cout << "Загаданное число больше" << endl;

            if (s == 5) {
                cout << "Вы проиграли. Было загадано:" << n << endl;
                break;
            }
        }

        cout << "Хотите начать сначала? (1 - ДА ): ";
        cin >> g;
        cout << endl;
        continue;
    }
    return 0;
}