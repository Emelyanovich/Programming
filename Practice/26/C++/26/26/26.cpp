#include <iostream>
#include <vector>
#include <cmath>

int randomInt (int range){
	int rawResult;
	rawResult = std::rand();
	return rawResult % range ;
}

template <typename T>
void printArr (std::vector<T> x, std::string before = ""){
	std::cout << before;
	for (auto& it : x)
		std::cout << it << ' ';
	std::cout << std::endl;
}

template <typename T>
std::vector<T> sort(std::vector<T> x, bool isAsc = true)