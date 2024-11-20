#include "dlist.hpp"
#include <cassert>
#include <iostream>

using namespace std;

dlist::node* dlist::newnode(int val)
{
	node* n = new node{val, nullptr, nullptr};

	return n;
}

/* **** Implement All the following methods ****
	
	Returns the node at a particular index (0 is the head). If n >= size()
	return nullptr; if n < 0, return the head of the list.
	Must run in 0(n) time.
*/
dlist::node* dlist::at(int n) const
{
	node* current = _head;
	while ( n > 0 && current != nullptr)
	{
		current = current->next;
		--n;
	}
	return current;			
}

dlist::node* dlist::_at(int n) const
{
	node* current = _tail;
	while( n > 0 && current != nullptr)
	{
		current = current->prev;
		--n;
	}

	return current;
}
	
/*
	Insert a new value, after an existing one. If previous == nullptr,
	then the list is assumed to be empty.
	Must run in 0(1) time.
*/
void dlist::insert(node *previous, int value)
{
	node* n = newnode(value);
	
	if (empty())
	{
		_head = n;
		_tail = n;
	}
	else
	{
		if (previous != nullptr)
		{
			n->prev = previous;
						
			if (previous->next == nullptr)
			{
				n->prev->next = n;
				_tail = n;
			}
			else
			{
				n->next = previous->next;
				previous->next = n;
				n->next->prev = n;
			}
		}
		else
		{
			n->next = _head;
			n->next->prev = n;
			_head = n;
		}
	
	}
	++sz;

} 									

/*
	Delete the given node. Should do nothing if which == nullptr. 
	Must run in 0(1) time.
*/
void dlist::remove(node* which)
{
	
	if (empty() or which == nullptr)
	{
		_head = nullptr;
		_tail = nullptr;
	}	
	else
	{
		node* p = which->prev;
		node* n = which->next;
	
		if (which != nullptr)
		{
			if (p != nullptr)
			{
				if (n != nullptr)
				{
					p->next = n;
					n->prev = p;
				}
				else
				{
					p->next = nullptr;
					_tail = p;
				}
			}
			else
			{
				if (n != nullptr)
				{
					n->prev = nullptr;
					_head = n;
					
				}
				else
				{
					_head = nullptr;
					_tail = nullptr;
				}
			}
		}
		--sz;
	}
	delete which;
	
}

/*
	Add a new element to the *end* of the list
	Must run in 0(1) time.
*/
void dlist::push_back(int value)
{
	insert(_tail, value);
}

/*
	Add a new element to the *beginning* of the list
	Must run in 0(1) time.
*/
void dlist::push_front(int value)
{
	insert(nullptr, value);

}

/*
	Remove the first element.
	If the list is empty, do nothing.
	Must run in 0(1) time.
*/
void dlist::pop_front()
{
	remove(_head);
}

/*
	Remove the last element.
	If the list is empty, do nothing.
	Must run in 0(1) time.
*/
void dlist::pop_back()
{
	remove(_tail);
}

/*
	Get the size of the list
	Should run in 0(n) time at the worst
*/
int dlist::size() const
{
	return sz;
}

/*
	Returns true if the list is empty
	Must run in 0(1) time
*/
bool dlist::empty() const
{
	return _head == nullptr and _tail == nullptr;

	/*
		if (_head == nullptr && _tail == nullptr)
			return true;
		return false;
	*/
}

/*
	Compare two lists for equality, return true if they have the same
	elements in the same positions.
	(Hint: it is *not* enough to just compare pointers! You have to
	compare the valuse stored in the nodes)
*/
bool operator== (const dlist& a, const dlist& b)
{
	
	if (a.size() == b.size())
	{
		int index = 0;
		
		while (a.at(index) != nullptr && b.at(index) != nullptr)
		{
			if (a.at(index)->value != b.at(index)->value)
			{
				return false;
			}
			++index;
		}
		return true;
	}
	return false;

}

/*
		a+b: Returns a new list consisting of all the elements of a, followed by all the
		elements of b(i.e., the list concatenatiion).

		Must run in 0(n) time in the length of the result (i.e., the length of a plus the
		length of b).
*/
dlist operator+ (const dlist& a, const dlist& b)
{
	if (a.empty())
	{
		return b;
	}
	
	if (b.empty())
	{
		return a;
	}

			
	dlist rlist;
	int size = a.size() + b.size();
	int forward = 0;
	dlist::node* current = a.head();
	
	while(current != nullptr)
	{
		rlist.push_back(current->value);
		if (current->next == nullptr && forward ==  size-1)
		{
			current = b.head();
		}
		else
		{
			current = current->next;
		}
		++forward;
	}
	return rlist;
/*	int size = a.size() + b.size();
	int forward = 0;
	int backward = size - 1;
	
	while (a.at(forward)->next != nullptr && b._at(backward) != nullptr)
	{
		if (forward + 1 == a.size())
		{
			a.at(forward)->next = b.head();
		}
		else if (backward + 1 == b.size())
		{
			b._at(backward)->prev = a.tail();
		}

		++backward;
		++forward;
	}

	return a;*/
}


/*
	reverse(1): Returns a new list that is th *reversal* of l; that is, a new list
	containing the same elements as 1 but in the reverse order.

	Must run in 0(n) time.
*/
dlist reverse(const dlist& l)
{
	dlist::node* current = l.head();
	dlist rlist;

	if (l.empty())
	{
		return rlist;
	}
	else 
	{
		while(current != nullptr)
		{
			rlist.push_front(current->value);
			current = current->next;
		}
		return rlist;
	}
	
}