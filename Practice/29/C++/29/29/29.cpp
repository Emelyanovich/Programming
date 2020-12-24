#include "stdafx.h"
#include <iostream>
#include <locale>

using namespace std;

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
        cout << "Введите фамилию и первую буква имени студента #" << i + 1 << ": ";
        cin >> stud[i].name;
        cout << endl << "Введите номер группы студента (целое число)#" << i + 1 << ": ";
        cin >> stud[i].group;
        cout << endl << "Введите результаты экзаменов по 5-ти бальной шкале #" << i + 1 << ": ";
        for (int j = 0; j < 5; j++)
        {
            cin >> stud[i].exams[j];
        }
    }
    cout << endl;
    for (int i = 0; i < count_students; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (((stud[i].exams[j]) == 3) || ((stud[i].exams[j]) == 4)) || (stud[i].exams[j]) == 5) )
            {
            cout << stud[i].fio << " " << stud[i].group;
            cout << endl;
            }
            else;
            {
                cout << "Not found";
                cout << endl;
            }
        }
    }
    cout << endl;
    system("pause");
    return 0;
}

