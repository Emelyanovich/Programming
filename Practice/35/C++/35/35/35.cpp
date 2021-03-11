#include <iostream>
#include <cstring>
#include "prog.h"

void create(IntArray& arr, int size)
{
    arr.data = new int[abs(size)];
    arr.size = abs(size);
}

void create(IntArray* arr, int size)
{
    create(*arr, size);
}

int get(IntArray& arr, int index)
{
    if (index < 0 or index >= arr.size)
    {
        return 0;
    }
    return arr.data[index];
}

int get(IntArray* arr, int index)
{
    return get(*arr, index);
}

void set(IntArray& arr, int index, int value)
{
    if (index < 0 or index >= arr.size)
    {
        exit(0);
    }
    arr.data[index] = value;
}

void set(IntArray* arr, int index, int value)
{
    set(*arr, index, value);
}

void print(IntArray& arr)
{
    std::cout << "[" << arr.data[0];
    for (int i = 1; i < arr.size; i++)
    {
        std::cout << ',' << arr.data[i];
    }
    std::cout << "]\n";
}

void print(IntArray* arr)
{
    print(*arr);
}

void resize(IntArray& arr, int newSize)
{
    if (newSize > arr.size)
    {
        int* newarr = new int[newSize];
        memcpy(newarr, arr.data, sizeof(int) * arr.size);
        for (int i = arr.size; i < newSize; i++)
        {
            newarr[i] = 0;
        }
        delete[] arr.data;
        arr.data = newarr;
        arr.size = newSize;
    }
    if (newSize < arr.size)
    {
        int* newarr = new int[newSize];
        memcpy(newarr, arr.data, sizeof(int) * newSize);
        delete[] arr.data;
        arr.data = newarr;
        arr.size = newSize;
    }
}

void resize(IntArray* arr, int newSize)
{
    resize(*arr, newSize);
}

void destroy(IntArray& arr)
{
    if (arr.data)
    {
        delete[] arr.data;
        arr.data = nullptr;
    }
    arr.size = 0;
}

void destroy(IntArray* arr)
{
    destroy(*arr);
}