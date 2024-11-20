#include <iostream>
#include <vector>
#include "ordered_array.hpp"

using namespace std;

int main()
{
	int capac = 10;
	ordered_array arr(capac);

	cout << arr.size() << endl;

	arr.insert(3);
	arr.insert(2);
	arr.insert(1);
	arr.insert(10);

	cout << arr.size() << endl;

	for (int i = 0; i < arr.size(); ++i)
	{
		cout << arr.at(i) << ", ";
	}
	return 0;	
}
