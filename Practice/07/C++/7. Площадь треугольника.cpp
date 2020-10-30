#include <iostream>
#include <cmath>
using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");

    double a, b, c, AB, BC, AC, xA, yA, xB, yB, xC, yC, P, S;
    int form;

    cout << "Выберите способ ввода параметров треугольника:" << endl;
    cout << "1. Длины сторон" << endl;
    cout << "2. Координаты вершин" << endl;

    
    cin >> form;
    if (form == 1) {
        cout << "Введите сторону a: "; cin >> a;
        cout << "Введите сторону b: "; cin >> b;
        cout << "Введите сторону c: "; cin >> c;
        if (a > b + c || b > a + c || c > a + b)
            cout << "Треугольника с данными длинами сторон не существует" << endl;
        else {
            P = (a + b + c) / 2;
            S = sqrt(P * (P - a) * (P - b) * (P - c));
            cout << "S = " << S;
        }

    }
        if (form == 2) {
        cout << "Введите вершины A через пробел: "; cin >> xA >> yA;
        cout << "Введите вершины B через пробел: "; cin >> xB >> yB;
        cout << "Введите вершины C через пробел: "; cin >> xC >> yC;
        AB = sqrt(pow((xB - xA), 2) + pow((yB - yA), 2));
        BC = sqrt(pow((xC - xA), 2) + pow((yC - yA), 2));
        AC = sqrt(pow((xB - xC), 2) + pow((yB - yC), 2));
        if (AB > BC + AC || BC > AB + AC || AC > AB + BC)
            cout << "Треугольника с данными длинами сторон не существует" << endl;
        else {
            P = (AB + BC + AC)/2;
            S = sqrt(P * (P - AB) * (P - BC) * (P - AC));
            cout << "S = " << S;
        }
        
        }
}