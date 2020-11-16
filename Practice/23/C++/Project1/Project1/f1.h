#include <iostream>
#pragma once

void Factorial() {
    using namespace std;
    int n, f;
    cin >> n;
    f = 1;

    if (n >= 0) {
        for (int i = 2; i <= n; i++) {
            f *= i;
        }
        cout << f << endl;
    }
}