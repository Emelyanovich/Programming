#include <iostream>
#include <vector>
#include <fstream>

using std::endl;
using std::vector;
using std::ostream;

#define PART 2

#if PART == 3
ostream& operator<< (ostream& out, const vector<int> vector)
{
	out << vector.size() << "\t| ";
	for (auto& item : vector)
	{
		out << &item << " ";
	}
	out << endl;
	return out;
}
#elif PART == 2
ostream& operator<< (ostream& out, const vector<int>& vector)
{
	out << vector.size() << "\t| ";
	for (auto& item : vector)
	{
		out << &item << " ";
	}
	out << endl;
	return out;
}
#endif

int main()
{
	srand(time(nullptr));
	vector<int> vector;
	std::ofstream data("data.txt");

	for (int i = 0; i < 64; ++i)
	{
		vector.push_back(rand());
		data << vector;
	}
	for (int i = 0; i < 63; ++i)
	{
		vector.pop_back();
		data << vector;
	}

	data.close();
}