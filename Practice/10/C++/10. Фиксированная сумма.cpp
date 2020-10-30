#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");

    int s, l1, r1, l2, r2;

    cout << "¬ведите через пробел число и два диапазона чисел (s l1 r1 l2 r2): ";
    cin >> s >> l1 >> r1 >> l2 >> r2;

    if (s < l1 + l2 && s > r1 + r2)
        cout << -1;
    else if (s - l1 <= r2)
        cout << l1 << " " << s - l1;
    else
        cout << s - r2 << " " << r2;
}
