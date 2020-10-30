#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");

    int n, f;
    cout << "Введите число: ";
    cin >> n;
    f = 1;

    for (int i = 2; i <= n; i++)
        f *= i;
    cout << "Факториал: " << f << endl;

    return 0;
}