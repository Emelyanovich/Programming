#include <iostream>
#include <vector>
using namespace std;

vector<int> DGenerator(unsigned int n)
{
	vector<int> dividers;
	int i = 1;
	while (true)
	{
		if (i == n)
		{
			dividers.push_back(i);
			break;
		}
		else if (n % i == 0 and i != 1)
		{
			n = n / i;
			dividers.push_back(i);
			i = 0;
		}
		i++;
	}
	return dividers;
}

void print_factorization(unsigned int n)
{
	vector<int> dividers;
	dividers = DGenerator(n);
	int size = dividers.size();

	cout << dividers[0];
	for (int i = 1; i < size; i++)
	{
		if (dividers[i - 1] == dividers[i])
		{
			int k = 1;
			while (dividers[i - 1] == dividers[i])
			{
				i++;
				k++;
				if (i == size)
				{
					break;
				}
			}
			cout << "^" << k;
			i--;
		}
		else
		{
			cout << "*" << dividers[i];
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	unsigned int n;
	cout << "Введите число\n";
	cin >> n;
	print_factorization(n);
}