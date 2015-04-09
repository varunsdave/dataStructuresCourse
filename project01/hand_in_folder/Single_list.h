#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

/*****************************************
 * UW User ID:  
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2011
 *
 * By submitting this file,  I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "ece250.h"
#include "Single_node.h"
#include "Exception.h"

template <typename Object>
class Single_list {
	private:
		Single_node<Object> *list_head;
		Single_node<Object> *list_tail;
		int node_count;

	public:
		Single_list();
		Single_list( const Single_list & );
		~Single_list();

		Single_list &operator = ( const Single_list & );

		// Accessors 

		int size() const;
		bool empty() const;

		Object front() const;
		Object back() const;

		Single_node<Object> *head() const;
		Single_node<Object> *tail() const;

		int count( const Object & ) const;

		// Mutators

		void push_front( const Object & );
		void push_back( const Object & );

		Object pop_front();

		int erase( const Object & );

	// Friends

	template <typename T>
	friend std::ostream &operator << ( std::ostream &, const Single_list<T> & );
};

template <typename Object>
Single_list<Object>::Single_list():list_head(0), list_tail(0), node_count(0) {
	// empty constructor
}

template <typename Object>
Single_list<Object>::Single_list( const Single_list<Object> &list ):list_head(0), list_tail(0), node_count(0) {
	
	*this = list;
}

//Destructor for the linked list.
//This function will continue to remove the first entry by calling pop_front method
//as long as the object is not empty.
// calls the empty method to check for empty method.
template <typename Object>
Single_list<Object>::~Single_list() {
	while (!empty())
	{
		pop_front();
	}
	
}

//the = operator used to copy a linked list 
//if the left hand side is not empty, it will first make it empty to copy the old data
//next, check if the right hand is empty, if it is no need to copy any data and return
//empty.
//Else create a new head and tail. Then loop through each node in the righ hand linked
//list. Create a new node for everynode in right linked list and add it to the list it
//is to be copied to.
//At the end update the node count and return
template <typename Object>
Single_list<Object> &Single_list<Object>::operator = ( const Single_list<Object> &rhs ) {
	// empty the current object
	while (!empty())
	{
		pop_front();
	}

	if (rhs.empty())
	{
		return *this;
	}
	/*list_head = new Single_node <Object>(rhs.front(),list_head);*/
	list_head = new Single_node <Object>(rhs.front());

	//list_tail = new Single_node(rhs.back());
	list_tail = list_head;
	for (Single_node<Object> *lhptr = head(), *rhptr =  rhs.head(); rhptr -> next()!=0;  rhptr = rhptr->next(), lhptr = lhptr ->next())
	{
		lhptr -> next_node = new Single_node <Object> (rhptr -> next()->retrieve () );
		list_tail = rhs.tail();
	}
	node_count = rhs.size();
	/*for (Single_node <Object> *lhptr = */
	// make a copy of the list rhs
	return *this;
}

//returns the node count of the linked list, which is the size
template <typename Object>
int Single_list<Object>::size() const {
	// enter your implementation here
	return node_count;
}

//check wheter or not the linked is is empty or not by comparing the head value
//it is true if head is 0 otherwise, it is false
template <typename Object>
bool Single_list<Object>::empty() const {
	// calls the empty function to check whether the list is empty of or not. If it is empty, returns true othewise false is returned. 
	
	if (list_head == 0)
	{	
		return true;
	}
	else
	{
		return false;
	}
	
}

//returns the first node in the linked list and checks if it is not empty. 
//Otherwise it throws an underflow error.
template <typename Object>
Object Single_list<Object>::front() const {
	// enter your implementation here
	//return Object();
	if (empty ())
	{
		throw underflow();
	}


	return list_head -> retrieve(); 
}

// returns the last object in the linked list if the list is not empty.
//Otherwise throws and underflow error
template <typename Object>
Object Single_list<Object>::back() const {
	// enter your implementation here
	//return Object();
	if (empty())
	{
		throw underflow();
	}
	return list_tail ->retrieve();
	
}

// returns the head of the linked list as a pointer
template <typename Object>
Single_node<Object> *Single_list<Object>::head() const {
	// enter your implementation here
	//return 0;
	return list_head;
}

// returns the tail of the linked list as a pointer
template <typename Object>
Single_node<Object> *Single_list<Object>::tail() const {
	// enter your implementation here
	//return 0;
	return list_tail;
}

//checks if the provided object in the parameter exists in the linked list.
// if it does returns an integer value of 1
// else returns 0.
//a forloop is used to step through every value in linked list, until the first value is found

template <typename Object>
int Single_list<Object>::count( const Object &obj ) const {
	// enter your implementation here
	for ( Single_node <Object> *pointers = head(); pointers!= 0 ; pointers = pointers -> next())
	{
		if (pointers ->retrieve() == obj)
		{
			return 1;
		}
	}
	return 0;
}

//push_front inserts a node in front of the linked list.
//first checks if the list is empty, if it is creates a new node and assigns
// head and tail to the node. Also updates counter when it is increased
//if it is not empty, insert the node in front by creating new pointer and
// update the new head. Update the counter
template <typename Object>
void Single_list<Object>::push_front( const Object &obj ) {
	// enter your implementation here
	if (empty())
	{
		list_head = new Single_node<Object> (obj,0);
		list_tail = list_head;
		node_count++;
		
	}
	else
	{
		list_head = new Single_node<Object> (obj, list_head);
		node_count++;
	}

}

//push_back inserts a node at the back of a linked list.
//if it empty, then insert an object at the back.
//else, enter the node towards the end and update list tail
//in either case it updates the node counter after inserting
template <typename Object>
void Single_list<Object>::push_back( const Object &obj ) {
	// enter your implementation here
	if (empty())
	{
		list_tail = new Single_node<Object>(obj, 0);
		list_head ->next_node = list_tail;
		node_count++;
	}
	else
	{
	Single_node <Object> *previous_tail;
	previous_tail = list_tail;

	list_tail = new Single_node<Object>(obj, 0);

	previous_tail ->next_node = list_tail;
	node_count++;

	}
}

//pop_front removes the first entry of the linked list and updates the pointers to 
//point to the next node.
//if it is empty it thorws an underflow error. Otherwise a temporary pointer is used
// to update the values. The temporary pointer points to the first node and at the end
// deletes the node. 
//if it the only node then, head and tail are set to 0. In either case node counter is
// decremented everytime
template <typename Object>
Object Single_list<Object>::pop_front() {
	// enter your implementation here
	if (empty() )
	{
		throw underflow();
	}
	Object e = front (); 
	Single_node <Object> *temp_pointer;
	
	if (size() == 1 )
	{
		temp_pointer = list_head;
		list_head = 0;
		list_tail = 0;
		
		delete temp_pointer;
		node_count--;
		
	}
	else
	{

		temp_pointer = list_head;
		list_head = temp_pointer ->next();
		delete temp_pointer;
		node_count --;
	}
	return e;
}

//erases the object passed in the parameter.
// a forloop finds the first instance the object is to be deleted if it exists. Otherwise, returns 0
// once the object is found a temp pointer is pointed to the node, and the list is updated. temp pointer 
//is deleted and node count is updated. Then returns 1 if it removed.
template <typename Object>
int Single_list<Object>::erase( const Object &obj ) {
	// enter your implementation here
	for ( Single_node <Object> *pointer = head(); pointer !=0; pointer = pointer ->next())
	{
		if (pointer ->retrieve () == obj)
		{
			pop_front();
			return 1;
		}

		else if ((pointer ->next())->retrieve() == obj )
		{	
			Single_node <Object> *temp_pointer = pointer ->next();
			pointer ->next_node = temp_pointer ->next_node ;
			delete temp_pointer;
			node_count --;
			return 1;
		}
			
	}
	
	return 0;
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator << ( std::ostream &out, const Single_list<T> &list ) {
	for ( Single_node<T> *ptr = list.head(); ptr != 0; ptr = ptr->next() ) {
		out << " -> " << ptr->retrieve();
	}

	out << " -> 0";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
