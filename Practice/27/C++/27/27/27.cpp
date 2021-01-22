#include <iostream>
#include<cmath>

void main() {
    int n; std::cout << "Введите число сигналов:", std::cin >> n;
    int* arr = int[n];

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];

        for (int j = 0; j < n; j++){
            for (int k = j + 1; k < n; k++)
            {
                if (arr[j] < arr[k])
                {
                    int temp = arr[k];
                    arr[k] = arr[j];
                    arr[j] = temp;
                }
            }
        }
        if (i == 0);
        std::cout << arr[0] << std::endl;
        
        }
    }
}