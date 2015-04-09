#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

/*****************************************
 * UW User ID:  
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2011
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "ece250.h"
#include "Double_node.h"
#include "Exception.h"

template <typename Object>
class Double_list {
	private:
		Double_node<Object> *list_head;
		Double_node<Object> *list_tail;
		int node_count; 

	public:
		Double_list();
		Double_list( const Double_list & );
		~Double_list();

		Double_list &operator = ( const Double_list & );

		// Accessors

		int size() const;
		bool empty() const;

		Object front() const;
		Object back() const;

		Double_node<Object> *head() const;
		Double_node<Object> *tail() const;

		int count( const Object & ) const;

		// Mutators

		void push_front( const Object & );
		void push_back( const Object & );

		Object pop_front();
		Object pop_back();

		int erase( const Object & );

	// Friends

	template <typename T>
	friend std::ostream &operator << ( std::ostream &, const Double_list<T> & );
};

template <typename Object>
Double_list<Object>::Double_list():list_head(0), list_tail(0), node_count(0) {
	// empty constructor
}

template <typename Object>
Double_list<Object>::Double_list( const Double_list<Object> &list ):list_head(0), list_tail(0), node_count(0) {
}

//Destructor for the linked list.
//This function will continue to remove the first entry by calling pop_front method
//as long as the object is not empty.
// calls the empty method to check for empty method.
template <typename Object>
Double_list<Object>::~Double_list<Object>()
{
	while (!empty() )
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
Double_list<Object> &Double_list<Object>::operator = ( const Double_list<Object> &rhs ) {
	while (!empty())
	{
		pop_front();
		
	}

	if (rhs.empty())
	{
		return *this;
	}

	list_head = new Double_node <Object>(rhs.front(),0,0);
	list_tail = list_head;
	for (Double_node<Object> *lhptr = head(), *rhptr =  rhs.head(); rhptr -> next()!=0;  rhptr = rhptr->next(), lhptr = lhptr ->next())
	{
		lhptr -> next_node = new Double_node <Object> (rhptr -> next()->retrieve () ,lhptr,0);
		list_tail = lhptr->next_node;
		
	}
	node_count = rhs.size();
	return *this;
}

//returns the node count of the linked list, which is the size
template <typename Object>
int Double_list<Object>::size() const {
	return node_count;
}

//check wheter or not the linked is is empty or not by comparing the head value
//it is true if head is 0 otherwise, it is false
template <typename Object>
bool Double_list<Object>::empty() const {
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
Object Double_list<Object>::front() const {
	if (empty ())
	{
		throw underflow();
	}

	
	return list_head -> retrieve(); 
}

// returns the last object in the linked list if the list is not empty.
//Otherwise throws and underflow error
template <typename Object>
Object Double_list<Object>::back() const {
	if (empty())
	{
		throw underflow();
	}
	return list_tail ->retrieve();
	
}

// returns the head of the linked list as a pointer
template <typename Object>
Double_node<Object> *Double_list<Object>::head() const {
	return list_head;
}

// returns the tail of the linked list as a pointer
template <typename Object>
Double_node<Object> *Double_list<Object>::tail() const {
	return list_tail;
}

//checks if the provided object in the parameter exists in the linked list.
// if it does returns an integer value of 1
// else returns 0.
//a forloop is used to step through every value in linked list, until the first value is found
template <typename Object>
int Double_list<Object>::count( const Object &obj ) const {
	for ( Double_node <Object> *pointers = head(); pointers!= 0 ; pointers = pointers -> next())
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
void Double_list<Object>::push_front( const Object &obj ) {
	if (empty())
	{
		list_head = new Double_node<Object> (obj,0,0);
		list_tail = list_head;
		node_count++;
		
	}
	else
	{
		Double_node<Object> *list_object = new Double_node<Object> (obj, 0,list_head);
		list_head ->previous_node = list_object;
		list_head = list_object;
		node_count++;
	}
}

//push_back inserts a node at the back of a linked list.
//if it empty, then insert an object at the back.
//else, enter the node towards the end and update list tail
//in either case it updates the node counter after inserting
template <typename Object>
void Double_list<Object>::push_back( const Object &obj ) {
	if (empty())
	{
		list_tail = new Double_node<Object>(obj, 0,0);
		list_head ->next_node = list_tail;
		node_count++;
	}
	else
	{
	Double_node<Object> *list_object = new Double_node<Object> (obj, list_tail, 0);
	list_tail ->next_node = list_object;
	list_tail = list_object;
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
Object Double_list<Object>::pop_front() {
	if (empty() )
	{
		throw underflow();
	}
	Object e = front();
	Double_node <Object> *temp_pointer;
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
		list_head = temp_pointer ->next_node;
		list_head->previous_node = 0;
		delete temp_pointer;

		node_count--;
	}
	return e;
	
}

//pop_back removes the last node in the linked list
template <typename Object>
Object Double_list<Object>::pop_back() {
	Object e = back();
	Double_node <Object> *temp_pointer;
	temp_pointer = list_tail;
	list_tail = temp_pointer ->previous_node;
	(temp_pointer ->previous_node)->next_node=0;

	delete temp_pointer;
	node_count--;
	return e;
}

//erases the object passed in the parameter.
// a forloop finds the first instance the object is to be deleted if it exists. Otherwise, returns 0
// once the object is found a temp pointer is pointed to the node, and the list is updated. temp pointer 
//is deleted and node count is updated. Then returns 1 if it removed.
template <typename Object>
int Double_list<Object>::erase( const Object &obj ) {
	for ( Double_node <Object> *pointer = head(); pointer !=0; pointer = pointer ->next())
	{
		if (pointer->retrieve() == obj)
		{
			pop_front();
			return 1;
		}
		else if ((pointer ->next())->retrieve() == obj )
		{	
			Double_node <Object> *temp_pointer = pointer ->next();
			pointer ->next_node = temp_pointer ->next_node ;
			 
			(pointer ->next_node)->previous_node = temp_pointer ->previous_node;
			//pointer = pointer ->next_node;
			delete temp_pointer;
			node_count --;
			return 1;
		}
			
	}
	
	return 0;
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator << ( std::ostream &out, const Double_list<T> &list ) {
	out << "head";

	for ( Double_node<T> *ptr = list.head(); ptr != 0; ptr = ptr->next() ) {
		out << " -> " << ptr->retrieve();
	}

	out << " -> 0" << std::endl << "tail";

	for ( Double_node<T> *ptr = list.tail(); ptr != 0; ptr = ptr->previous() ) {
		out << " -> " << ptr->retrieve();
	}

	out << " -> 0";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
