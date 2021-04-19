#include <Windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include "point.h"


const auto PI = 3.141592653589793;

int main() {
    std::vector<Point> original;
    std::ifstream fin("data.txt");
    if (!fin.is_open()) {
        std::cout << "Can't open file" << std::endl;
        return 1;
    } else {
        while (!fin.eof()) {
            Point p;
            fin >> p;
            fin.ignore(2);
            original.push_back(p);
        }
        fin.close();
    }

    std::vector<Point> simulacrum(original);
    for (auto& p : simulacrum) {
        std::cout << p;
        p.set_x(p.get_x() + 10);
        p.set_phi(p.get_phi() + 180*PI/180);
        p.set_y(-p.get_y());
        p.set_x(-p.get_x() - 10);
        std::cout << p << std::endl;
    }

    if (std::equal(original.begin(), original.end(), simulacrum.begin()))
        std::cout << "\nIt works!\n";
    else
        std::cout << "\nIt not works!\n";
}