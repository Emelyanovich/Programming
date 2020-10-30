#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");

    double a = 9.8;
    double x0, v0, t;
    cout << "Введите через пробел значения для x0, v0, t: ";
    cin >> x0 >> v0 >> t;
    cout << x0 + v0 * t - (a * t * t) / 2;

    //Ответ: Для С++ надо брать тип данных с плавающей точкой, для более точных расчетов.
}