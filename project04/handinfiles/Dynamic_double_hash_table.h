#ifndef DYNAMIC_DOUBLE_HASH_TABLE_H
#define DYNAMIC_DOUBLE_HASH_TABLE_H

/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename Object>
class Dynamic_double_hash_table
{
	private:
		int power;
		int count;
		int deleted_count;
		int array_size;
		int initial_size;

		Object *array;
		state *occupied;

		int h1( const Object & ) const;
		int h2( const Object & ) const;
	public:
		Dynamic_double_hash_table( int = 5 );
		~Dynamic_double_hash_table();
		int size() const;
		int capacity() const;
		double load_factor() const;
		double deleted_factor() const;
		bool empty() const;
		bool member( const Object & ) const;
		Object bin( int ) const;

		void print() const;

		void insert( const Object & );
		void double_hash (const Object &);
		void half_hash(const Object &);
		void re_hash(const Object &);
		bool remove( const Object & );
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator << ( std::ostream &, const Dynamic_double_hash_table<T> & );
};

template<typename Object>
Dynamic_double_hash_table<Object>::Dynamic_double_hash_table( int m ):
	power( m ), count( 0 ), deleted_count( 0 ),
	array_size( 1 << power ),
	initial_size( 1 << power ),
	array( new Object[array_size] ),
	occupied( new state[array_size] )
{
	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = EMPTY;
	}
}

template<typename Object>
Dynamic_double_hash_table<Object>::~Dynamic_double_hash_table() {
	delete  []array;
	delete [] occupied;
}

template<typename Object>
int Dynamic_double_hash_table<Object>::size() const {
	return count;
}

template<typename Object>
int Dynamic_double_hash_table<Object>::capacity() const {
	return array_size;
}

template<typename Object>
double Dynamic_double_hash_table<Object>::load_factor() const {
	return static_cast<double>(static_cast<double>(count)/array_size);
}

template<typename Object>
double Dynamic_double_hash_table<Object>::deleted_factor() const {
	return  static_cast<double>(static_cast<double>(deleted_count)/array_size);
}

template<typename Object>
bool Dynamic_double_hash_table<Object>::empty() const {
	return (count==0);
}

template<typename Object>
int Dynamic_double_hash_table<Object>::h1( const Object & obj ) const {
	int result = static_cast<int>( obj ) & (array_size - 1);

	return result < 0 ? (result + array_size) : result;
}

template<typename Object>
int Dynamic_double_hash_table<Object>::h2( const Object & obj ) const {
	int result = (static_cast<int>( obj ) / array_size) & (array_size - 1);

	return (result < 0) ? ((result + array_size) | 1) : (result | 1);
}

template<typename Object>
bool Dynamic_double_hash_table<Object>::member( const Object & obj ) const {
	int initial = h1(obj);
	int jump = h2(obj);
	int place;

	for (int i = 0; i < array_size; ++i) {
		place = (initial + i*jump) & (array_size - 1);

		if (array[place] == obj)
		{
			return true;
		}
		else if (occupied[place] == EMPTY) 
		{
			return false;
		}
	}

	
	return false;
}

template<typename Object>
Object Dynamic_double_hash_table<Object>::bin( int n ) const {
	// DO NOT CHANGE
	return array[n];
}

template<typename Object>
void Dynamic_double_hash_table<Object>::insert( const Object & obj )
{
	
	if (member(obj))
	{
		return;
	}
	else
	{
		// if the load is greater than or equal to 0.75 then re-has by doubling the size
		if (load_factor()>=0.75)
		{
			Object * temp_array = array;
			state * temp_occupied = occupied;
			int temp_array_size = array_size;
			array = new  Object[2*array_size];
			occupied = new state[2*array_size];
			array_size = array_size*2;
			count = 0;
			// call the doubling function
			for ( int i = 0; i < array_size; ++i ) 
			{
				occupied[i] = EMPTY;
			}
			
			for (int i = 0; i < temp_array_size; ++i)
			{
				//place = (initial + i*jump) & (array_size - 1);
				if ((temp_occupied[i] ==OCCUPIED))
				{
					double_hash(temp_array[i]);

				}
			}
			
			
	delete [] temp_array;
	delete [] temp_occupied;
		}
		int initial = h1(obj);
	int jump = h2(obj);
	int place;
	
		
			
			for (int i = 0; i < array_size; ++i)
			{
				place = (initial + i*jump) & (array_size - 1);
				if ((occupied[place] == EMPTY) ||(occupied[place] == DELETED))
				{
					array[place] = obj;
					occupied[place] = OCCUPIED;
					count ++;
					return;
				}
				
			}

		
	}
}

template<typename Object>
void Dynamic_double_hash_table<Object>::double_hash( const Object & obj )
{
	insert(obj);
}


template<typename Object>
void Dynamic_double_hash_table<Object>::half_hash( const Object & obj )
{
	/*int initial = h1(obj);
	int jump = h2(obj);
	int place;*/

	Object * temp_array = array;
	state * temp_occupied = occupied;
	int temp_array_size = array_size;
	array = new  Object[array_size/2];
	occupied = new state[array_size/2];
	array_size = array_size/2;
	count = 0;
	
	// call the doubling function
	for ( int i = 0; i < array_size; ++i ) 
	{
		occupied[i] = EMPTY;
	}
			
	for (int i = 0; i < temp_array_size; ++i)
	{
		//place = (initial + i*jump) & (array_size - 1);
		if ((temp_occupied[i] ==OCCUPIED))
		{
			double_hash(temp_array[i]);

		}

	}
	
	delete [] temp_array;
	delete [] temp_occupied;
}
template<typename Object>
void Dynamic_double_hash_table<Object>::re_hash( const Object & obj )
{
	/*int initial = h1(obj);
	int jump = h2(obj);
	int place;*/
	//std::cout << *this;
	Object * temp_array = array;
	state * temp_occupied = occupied;
	int temp_array_size = array_size;
	array = new  Object[array_size];
	occupied = new state[array_size];
	array_size = array_size;
	deleted_count =0;
	count = 0;
	// call the doubling function
	for ( int i = 0; i < array_size; ++i ) 
	{
		occupied[i] = EMPTY;
	}
			
	for (int i = 0; i < temp_array_size; ++i)
	{
		
		//place = (initial + i*jump) & (array_size - 1);
		//std::cout <<" current object - " << temp_array[i] << std::endl;
		if ((temp_occupied[i] ==OCCUPIED))
		{
			double_hash(temp_array[i]);

		}
	}
	delete [] temp_array;
	delete [] temp_occupied;
}
template<typename Object>
bool Dynamic_double_hash_table<Object>::remove( const Object & obj ) 
{
	int initial = h1(obj);
	int jump = h2(obj);
	int place;

	if(!member(obj))
	{
		return false;
	}
	for (int i = 0; i < array_size; ++i)
	{
		place = (initial + i*jump) & (array_size - 1);
		if (occupied[place] == OCCUPIED && array[place] == obj)
		{
			
			occupied[place] = DELETED;
			count --;
			deleted_count++;
			//std::cout << array[place] << std::endl;
	//		std::cout << " removing object: " << obj << "- from "<< *this;
			if (load_factor()<= 0.25 && capacity()> initial_size)
			{
				half_hash(obj);
				return true;
			}
			else if (deleted_factor ()==0.25)
			{
				/*std::cout << *this;*/
				re_hash(obj);
				//std::cout << *this;
				return true;
			}
		return true;
		}
				
	}
}

template<typename Object>
void Dynamic_double_hash_table<Object>::clear() {
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator << ( std::ostream &out, const Dynamic_double_hash_table<T> &list ) {
	/*for (int i =0; i < list.array_size; i++)
	{
		out << "array at " << i << " is " << list.array[i] << std::endl;
	}
	return out;*/
	if ( list.empty() ) {
                out << "HASH TABLE IS EMPTY" << std::endl;
                return out;
        }

        for ( int i = 0; i < list.array_size; ++i ) {
                if ( list.occupied[i] == OCCUPIED ) {
                        out << "Bin " << i << ": " << list.array[i] << std::endl;
                } else if ( list.occupied[i] == DELETED ) {
                        out << "Bin " << i << ": DELETED" << std::endl;
                } else if ( list.occupied[i] == EMPTY ) {
                        out << "Bin " << i << ": EMPTY" << std::endl;
                }
        }

        return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
