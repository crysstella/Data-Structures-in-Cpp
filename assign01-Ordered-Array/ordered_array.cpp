#include <iostream>
#include <stdexcept> 		// For out_of_range
#include <algorithm>
#include <vector>
#include "ordered_array.hpp"

using namespace std;

/* If size() == n for some unknown n, approx. how much time will the method take, in terms of n?
   For example, if method examines each element of the array twice, you might say it will take roughly 2n
   time to run.	
 */
 
ordered_array::ordered_array::ordered_array(int cap)
{
	cout << "Constructing new array, capacity = " << cap << endl;
	arr = {};
	capac = cap;
}

ordered_array::~ordered_array()
{
		
}

/*
	size() = n 
	Best case: (full) 0 subscipts, 0 assignments
		**Run time: 0
	Worst case: arr.push_back(elem) : 1 subscripts (not sure)
				distance between begin and end arr element: n
				
		** Run time: nlog(n)
		
*/
void ordered_array::insert(int elem)
{
	if (not full())
	{
		if (in_domain(elem))
		{
			arr.push_back(elem);
			sort(arr.begin(), arr.end());
		}
	}
}

/*
	size() = n
	If the elem exists in the arr:
	   - The exists() method takes (i+1) times to run.
	   - When the element exists, the method will return true/false
	   it means the loop or the method is already finished. 
	   - The for loop in remove() will be executed. 
	   - It is similar to the exists() method:
	   		**  The element in arr that contains the elem value
				will be removed; so the loop also stops.
				We can say that the time that remove() runs depends on i.
				In other words, it takes (i+1) times for the method to run
				while i < n. 
   [ So remove() method takes i + 1 times to run.
==>[ i < n => 2i < 2n => 2i + 2 < 2n + 2
   [ The remove() method takes approximately 2n + 2 times to run or less.

   Best case: (not in domain) 0 assignments, 0 subscripts
   		** Run time: 0
   Worst case: n + n subscripts, 0 assignments, n comparisons   	 
   		** Run time: 2n 
*/	   

void ordered_array::remove(int elem)
{	
	if (in_domain(elem))
	{
		if (exists(elem))
		{
			for (int i = 0; i < arr.size(); i++)
			{
				if (elem == at(i))
				{
					arr.erase(arr.begin() + i);
					break;
				}
			}
		}
	}
}

/*
	size() = n
	If the elem exists in the arr:
		   - The exists() method takes (i+1) times to run.
		   - When the element exists, the method will return true/false
		   it means the loop or the method is already finished. 
	i + 1 < n + 1
	==> So exists() takes approx n + 1 times to run. 

	Best case: 1 subscript, 0 assignments	(return true), 1 == comparisons
		** Run time: 1
	Worst case: n subscripts, 0 assignments, n comparisons 
		** Run time: n

	
*/
bool ordered_array::exists(int elem)
{
	for (int i = 0; i < arr.size(); i++)
	{
		if (elem == at(i))
		{
			return true;
		}
	}
	return false;
}

int ordered_array::at(int i)
{
	if (i >= 0 and i < size())
	{
		return arr[i];
	}
	else
	{
		throw out_of_range("Index out of range!");
	}
}