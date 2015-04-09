#ifndef UNDO_REDO_STACK_H
#define UNDO_REDO_STACK_H

/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#include "ece250.h"
#include "Single_list.h"
#include "Exception.h"

template <typename Object>
class Undo_redo_stack {
	private:
		Single_list<Object> undo_stack;
		Single_list<Object> redo_stack;

	public:
		bool can_undo() const;
		bool can_redo() const;

		void event( const Object & );
		Object undo();
		Object redo();
		void clear();
};

template <typename Object>
bool Undo_redo_stack<Object>::can_undo() const 
{
	
	if (undo_stack.empty())
	{
		return false;
	}
	return true;
}

template <typename Object>
bool Undo_redo_stack<Object>::can_redo() const {
	if (redo_stack.empty())
	{
		return false;
	}
	return true;
}

template <typename Object>
void Undo_redo_stack<Object>::event( const Object & obj ) {
	while (!redo_stack.empty())
	{
		redo_stack.pop_front();
	}
	
	undo_stack.push_front(obj);
	
}

template <typename Object>
Object Undo_redo_stack<Object>::undo() 
{
	if (!can_undo())
	{
		throw underflow();
	}
	Object obj =undo_stack.pop_front();
	redo_stack.push_front(obj);
	return obj;
}

template <typename Object>
Object Undo_redo_stack<Object>::redo() 
{
	if ( !can_redo())
	{
		throw underflow();
	}
	Object obj =redo_stack.pop_front();
	undo_stack.push_front(obj);
	return obj;
}

template <typename Object>
void Undo_redo_stack<Object>::clear() 
{
	while (!redo_stack.empty())
	{
		redo_stack.pop_front();
	}
	while (!undo_stack.empty())
	{
		undo_stack.pop_front();
	}
}


// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator << ( std::ostream &out, const Undo_redo_stack<T> &stack ) {
	// write code to output stack

	out << " ";

	return out;
}


#endif
