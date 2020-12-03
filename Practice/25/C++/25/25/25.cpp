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