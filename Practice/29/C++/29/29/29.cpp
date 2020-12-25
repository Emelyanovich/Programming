#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>
#include <locale>


struct Student
{
    char name[10];
    int group;
    int exams[5];
}

int main();
{
    setlocale(LC_ALL, "rus");
    int count_students = 2;
    Student* stud = new Student[count_students];
    for (int i = 0; i < count_students; i++)
    {
        std::cout << "Введите фамилию и первую буква имени студента #" << i + 1 << ": ";
        std::cin >> stud[i].name;
        std::cout << endl << "Введите номер группы студента (целое число)#" << i + 1 << ": ";
        std::cin >> stud[i].group;
        std::cout << endl << "Введите результаты экзаменов по 5-ти бальной шкале #" << i + 1 << ": ";
        for (int j = 0; j < 5; j++)
        {
            std::cin >> stud[i].exams[j];
        }
    }
    cout << endl;
    std::vector<Student>ozenka_dva;
    for (int i = 0; i < 10; i++) {
        if ((vec[i].exams["Math"] == 2) || (vec[i].exams["Phys"] == 2) ||
            (vec[i].exams["Hist"] == 2) || (vec[i].exams["Prog"] == 2)) {
            ozenka_dva.push_back(vec[i]);
        }
    }

    std::cout << BozoSort(ozenka_dva) << std::endl;
    std::cout << "Expulsion" << "\n\n";
    srand(time(NULL));
    if (ozenka_dva() > 0) {
        std::cout << ozenka_dva[rand() % ozenka_dva.size()];
    }
    else {
        std::cout << "Not found";
    }
 
    cout << endl;
    system("pause");
    return 0;
}

