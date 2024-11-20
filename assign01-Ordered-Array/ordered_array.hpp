#ifndef ordered_array_hpp
#define ordered_array_hpp

#include <iostream>
#include <climits>
#include <vector>

using namespace std;

class ordered_array
{
	private:
		int capac;
		vector <int> arr;
		
		bool in_domain(int elem) const
		{
			return (elem < INT_MAX and elem > INT_MIN);
        } 
         	
        bool in_range() const
        {
            return (size() <= capacity() and size() > 0);
        }
      
	public:
		//constructor
		ordered_array(int cap);

		//destructor
		~ordered_array();

		//size()
		int size() const { return arr.size();}

		//capacity()
		int capacity() const { return capac;}

		bool full() const {return capacity() == size(); }
		bool empty() const {return size() == 0;}
		
		//insert
		void insert(int elem);

		//remove
		void remove(int elem);

		// exits
		bool exists(int elem);

		/*	at(i)
			Returns the value in the array at index i, which should be >=0 and < size()
		 */
		 int at(int i);
};

#endif		
