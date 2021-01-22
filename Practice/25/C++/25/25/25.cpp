#include <iostream>
#include <clocale>
#include <vector>
#include <ctime>

using namespace std;
enum Order { up, down };

bool check( vector < int > & x , Order order)
{
	switch (order)
	{
	case up:
		for (int i = 0; i < x.size() - 1; i++)
		{
			if (x[i] > x[i + 1]) {
				return false;
				break;
			}
		}
		break;
	case down:
		for (int i = 0; i < x.size() - 1; i++) 
		{
			if (x[i] < x[i + 1]) 
			{
				return false;
				break;
			}
		}
		break;
	}

	return true;
}
bool check(int x, int y, int z, Order order) 
{
	switch (order) {
	case up:
		if (y > z || x > y || x > z) return false;
		break;
	case down:
		if (y < z || x < y || x < z) return false;
		break;
	}
	return true;
}
void BozoSort(vector<int>& x, Order order = up) {
	bool sorted = check(x, order);
	while (!sorted) {
		int index1 = rand() % x.size();
		int index2 = rand() % x.size();

		int temp = x[index2];
		x[index2] = x[index1];
		x[index1] = temp;

		sorted = check(x, order);

	}
}
void BozoSort(int& k, int& m, int& n, Order order = up) {
	bool sorted = check(k, m, n, order);
	int temp;
	while (!sorted) {
		int index = rand() % 3;

		switch (index) {
		case 0:
			temp = k;
			k = m;
			m = temp;
			break;
		case 1:
			temp = k;
			k = n;
			n = temp;
			break;
		case 2:
			temp = n;
			n = m;
			m = temp;
			break;
		}
		sorted = check(k, m, n, order);
	}
}

void print(vector<int> x) {
	for (int i = 0; i < x.size(); i++) cout << x[i] << " ";
	cout << endl << endl;
}


void print(int x, int y, int z) {
	cout << x << " " << y << " " << z << endl << endl;
}

int main() {
	setlocale(LC_ALL, "russian");
	srand(time(0));
	int n;
	cin >> n;
	int* x = new int[n];

	for (int i = 0; i < n; i++) cin >> x[i];

	vector<int> y;
	for (int i = 0; i < n; i++) {
		y.push_back(x[i]);
	}

	int k = y[0], m = y[1], n = y[2];
	
	std::cout << endl;
	BozoSort(y, up);
	print(y);
	BozoSort(y, down);
	print(y);
	BozoSort(y, up);
	print(y);
	BozoSort(y, down);
	print(y);
	BozoSort(k, m, n, up);
	print(k, m, n);
	BozoSort(k, m, n, down);
	print(k, m, n);
	return 0;
}