#ifndef DYNAMIC_QUEUE_AS_ARRAY_H
#define DYNAMIC_QUEUE_AS_ARRAY_H

/*****************************************
 * UW User ID:  
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2011
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#include "ece250.h"
#include "Exception.h"

template <typename Object>
class Dynamic_queue_as_array
{
	private:
		int initial_size;
		int array_size;
		Object *array;
		// other integer member variables, as necessary
		int ihead;
		int itail;
	//	int count;
		int array_capacity;


	public:
		Dynamic_queue_as_array( int = 10 );
		Dynamic_queue_as_array( const Dynamic_queue_as_array & );
		~Dynamic_queue_as_array();

		Dynamic_queue_as_array &operator = ( const Dynamic_queue_as_array & );

		Object head() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void enqueue( const Object & );
		Object dequeue();
		void clear();
	//	void Output();

	// Friends

	template <typename T>
	friend std::ostream &operator << ( std::ostream &, const Dynamic_queue_as_array<T> & );
};

template <typename Object>
Dynamic_queue_as_array<Object>::Dynamic_queue_as_array( int n ): 
	initial_size(std::max(1,n)),
	array_size(0),
	ihead(0),
	itail(-1),
	//count(0),
	array_capacity (initial_size),
	array( new Object[initial_size])
	{
		//empty constructor
	}

template <typename Object>
Dynamic_queue_as_array<Object>::Dynamic_queue_as_array( const Dynamic_queue_as_array<Object> &queue ) :
	initial_size(queue.size()),
	array_size(queue.size()),
	ihead(0),
	itail(-1),
	//count(0),
	array_capacity (array_size),
	array( new Object[initial_size]){
	// Initialize your object and then call operator=
	*this = queue;
}

template <typename Object>
Dynamic_queue_as_array<Object>::~Dynamic_queue_as_array() {

	delete [] array;
}

template <typename Object>
Dynamic_queue_as_array<Object> &Dynamic_queue_as_array<Object>::operator = ( const Dynamic_queue_as_array<Object> &rhs ) {
	// empty the current queue, if necessary, deallocating memory
	// make a copy of the queue rhs
	if (rhs.empty())
	{
	return *this;
	}
	delete [] array;
	array = new Object [rhs.capacity()];
	initial_size = rhs.capacity();
	array_size = rhs.size();
	ihead = rhs.ihead;
	itail =ihead -1;
	//count = rhs.array_size;
	array_capacity = rhs.capacity();
	//store ihead place so that it can be edited
	int counter = rhs.ihead;
	for (int i =0; i<rhs.size(); i++)
	{
		
		if (counter > array_capacity)
		{
			counter = 0;
		}
		
		array[i] = rhs.array[counter];
		counter++;
		array_size++;
		
	}
	//restore original ihead value
//	rhs.ihead = counter;

	return *this;
}

template <typename Object>
int Dynamic_queue_as_array<Object>::size() const {

	return array_size;
}

template <typename Object>
int Dynamic_queue_as_array<Object>::capacity() const {
	return array_capacity;
}

template <typename Object>
bool Dynamic_queue_as_array<Object>::empty() const {
	if (itail == -1)
	{
		return true;
	}
	else
		return false;
}

template <typename  Object>
Object Dynamic_queue_as_array<Object>::head() const {
	if (array_size==0)
	{
		throw underflow();
	}

	return array[ihead];
}

template <typename Object>
void Dynamic_queue_as_array<Object>::enqueue( const Object &obj ) 
{
	
	if (array_size == capacity())
	{
		int t_size= array_size;
		Object *temp_array = new Object [t_size];
	
		for (int i =0; i < array_size; i++)
		{
			temp_array[i] = head() ;
			
			
			ihead++;
			if (ihead > array_capacity)
			{
				ihead = 0;
			}
		}
	
		// may need to delete
		delete [] array;
		// double the array size and then implelemt the insertion
		array = new  Object [(2*array_capacity)];
		ihead = 0;
		itail = -1;
		array_size = t_size;
		
		for (int i =0; i< t_size; i++)
		{
			array[i] = temp_array[i];
			++itail;
		
		}
	
	/*	ihead = 0;
		itail = array_capacity;*/
		array_capacity = array_capacity*2; 

		// insert the enque element
		++itail;
		array[itail] = obj;
		array_size++;
		delete []temp_array;
	}
	else
	{
		++itail;
		if (itail > capacity())
		{
			itail = 0;
		}
		array[itail] = obj;
		array_size++;
		 
	}
	
}

template <typename Object>
Object Dynamic_queue_as_array<Object>::dequeue() {

	if (array_size == 0)
	{
		throw underflow();
	}
	

	Object temp_object= array[ihead];
	if(ihead == array_capacity)
	{
		
		ihead = 0;
	}
	else
	{
		
		ihead++;
	}
	array_size--;

	if ( (array_size <= (array_capacity/4)) && ( array_size/2 >= initial_size))
	{	
		Object *temp_array = new Object [array_size];

		for (int i =0; i < array_size ; i++)
		{
			if (ihead > array_capacity)
			{
				ihead = 0;
			}
			temp_array[i] = head() ;
			ihead++;
		}
		// may need to delete
		delete [] array;
		array = new Object [array_capacity/2];
		ihead =0;
		itail = -1;
		array_capacity = array_capacity/2;
		for (int i =0; i < (array_size); i++)
		{
			array[i] = temp_array[i];
			array_size++;
		}
		delete [] temp_array;
	}
	
	return temp_object;
}

template <typename Object>
void Dynamic_queue_as_array<Object>::clear()
{
	delete []array;
	array = new Object [initial_size];
	initial_size = initial_size;
	array_size = initial_size;
	ihead = 0;
	itail = -1;
	array_capacity = 0;

}

// You can modify this function however you want:  it will not be tested


template <typename T>
std::ostream &operator << ( std::ostream &out, const Dynamic_queue_as_array<T> &queue ) {
	// I don't know how you are implementing your queue so I cannot print it.
	// If you want, you can print whatever you want here and then call cout
	// in the driver.

	// Remember to redirect to out, e.g.,
	//      out << "Hello!";

	return out;
}
//template <typename Object>
//void Dynamic_queue_as_array<Object>:: Output()
//{
//	
//	int counter = ihead;
//	for (int i =0; i<array_size; i++)
//	{
//		
//		std::cout<< "element at { "<< i <<" } is : "<<array[counter]<< endl;
//		if (counter == capacity())
//		{
//			counter = -1;
//		}
//		counter++;
//		
//	}
//	
//	
////	return out;
//}
//
//// Is an error showing up in ece250.h or elsewhere?
//// Did you forget a closing '}' ?

#endif
