#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file,  I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "ece250.h"

template <typename Object>
class Single_list;

template <typename Object>
class Cyclic_list;

template <typename Object>
class Sentinel_list;

template <typename Object>
class Cyclic_sentinel_list;

template <typename Object>
class Single_node {
	private:
		Object       element;
		Single_node *next_node;


	public:
		Single_node( const Object & e = Object(), Single_node *n = 0 );

		Object retrieve() const;
		Single_node *next() const;

		friend class Single_list<Object>;
		friend class Cyclic_list<Object>;
		friend class Sentinel_list<Object>;
		friend class Cyclic_sentinel_list<Object>;

		// if ptr is a pointer to a Single_node<Object> object
		// in one of the friendly classes, you should:
		//    use   this -> next_node   to modify it
		//    use   this -> next()      to access it
};

template <typename Object>
Single_node<Object>::Single_node( const Object &e, Single_node<Object> *n ):element( e ), next_node( n )
{
	// empty constructor
}

// return the element as an object.
template <typename Object>
Object Single_node<Object>::retrieve() const
{
	// enter your implementation here
	return element;
}
// returns the pointer to the next node
template <typename Object>
Single_node<Object> *Single_node<Object>::next() const
{
	// enter your implementation here
	return next_node;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
