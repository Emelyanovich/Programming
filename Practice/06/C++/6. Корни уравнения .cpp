#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");

    double a, b, c, d;
    cout << "¬ведите число a: ";
    cin >> a;
    cout << "¬ведите число b: ";
    cin >> b;
    cout << "¬ведите число c: ";
    cin >> c;

    d = b * b - 4 * a * c;

    if (a == 0)
        cout << "один корень: " << -c / b << endl;
    else if (d > 0) {
        cout << "первый корень: " << (-b + sqrt(d)) / (2 * a) << endl;
        cout << "второй корень: " << (-b - sqrt(d)) / (2 * a) << endl;
    }
    else if (d == 0)
        cout << "один корень: " << -b / (2 * a) << endl;
    else
        cout << "уравнение не имеет корней" << endl;

    return 0;
}