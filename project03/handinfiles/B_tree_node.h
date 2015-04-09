#ifndef B_TREE_NODE_H
#define B_TREE_NODE_H

/*****************************************
 * UW User ID:  
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2011
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "ece250.h"
#include "Exception.h"

template <typename Object>
class B_tree;

template <typename Object>
class B_tree_node {
	private:
		const static int N;

		int          num_elements;
		bool         is_leaf;
		Object       elements[5];
		B_tree_node *subtrees[5];

	public:
		B_tree_node( bool = true );
		B_tree_node( B_tree_node *, B_tree_node * );
		~B_tree_node();


		Object		  find_min(B_tree_node *)const;
		B_tree_node   *find_max(Object const &); 
		Object        retrieve( int ) const;
		B_tree_node  *subtree( int ) const;
		int           size() const;
		bool          leaf() const;
		bool          empty() const;
		bool          full() const;
		int           count( Object const & ) const;

		int			  insert_place( Object const &) ;
		
		void          draw( int = 0 ) const;
		static void   space( int = 0 );
				

		B_tree_node  *insert( Object const & );
		B_tree_node *insert_object(Object const &, B_tree_node <Object> const &);
};

template <typename Object>
const int B_tree_node<Object>::N = 5;

template <typename Object>
B_tree_node<Object>::B_tree_node( bool lf ):num_elements( 0 ), is_leaf( lf ) 
{
	// set all the pointers to 0
	for (int i = 0; i < N; i++)
	{
		subtrees[i]=0;
	}
}

template <typename Object>
B_tree_node<Object>::B_tree_node( B_tree_node<Object> *first, B_tree_node<Object> *second ):num_elements( 2 ), is_leaf( false ) {
	subtrees[0] = first;
	subtrees[1] = second;

	elements[0] = first -> find_min(first);
	elements[1] = second -> find_min(second);
	

}

template <typename Object>
Object B_tree_node<Object>::find_min(B_tree_node<Object> *node ) const
{
	
	if (node ->leaf())
	{
		return node-> elements[0];
	}
	else
	{
		
		// if it is not then recusively find the min
		for (int i =0; i < node->num_elements; i++)
		{
			return (subtrees[i]->find_min(subtrees[i]));

		}

		return 0;
	}
}  
template <typename Object>
B_tree_node<Object>::~B_tree_node()
{
	for (int i =0; i < num_elements; i++)
	{
		//	delete elements[i];
		delete subtrees[i];
	}	
}

template <typename Object>
bool B_tree_node<Object>::leaf() const {
	// check if the current node is a leaf and return the value appropriately.
	// A true is retuned if it is a leaf, false otherwise
	if (is_leaf)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//template <typename Object>
//void B_tree_node<Object>::find_min() const {}
template <typename Object>
int B_tree_node<Object>::size() const {
	if (leaf()) 
	{
		return num_elements;
	} 
	else 
	{
		int sum = 0;
		for (int i = 0; i<num_elements; i++)
		{
			sum = sum + (subtrees[i] -> size());
		}
		return sum;
	}
}

template <typename Object>
bool B_tree_node<Object>::full() const {
	// check if the node has 5 elements. If so then it is full, otherwise is empty
	// return appropriately.
	if (num_elements == 5)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename Object>
bool B_tree_node<Object>::empty() const {
	// compare the number of elements. 
	// A node returns true if the number of elements is set to 0
	// A node retruns false if the number of elements is not 0
	/*if (num_elements == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
*/
	return( (num_elements==0));
	
}

template <typename Object>
int B_tree_node<Object>::count( Object const &obj ) const {
	
	int counter =0;
	for (int i =0; i < N; i++)
	{
		if (elements[i] == obj)
		{
			counter = i;
			return counter;
		}
	}
	return counter;
}

template <typename Object>
Object B_tree_node<Object>::retrieve( int n ) const {
	if (n> num_elements || n < 0)
	{
		throw out_of_bounds();
	}

	return elements[n];
}

template <typename Object>
B_tree_node<Object> *B_tree_node<Object>::subtree( int n ) const {
	if (n<0 || n > num_elements)
	{
		throw out_of_bounds();
	}
	else
	{
		return subtrees[n];
	}
	return 0;
}

template <typename Object>
B_tree_node<Object> *B_tree_node<Object>::insert( const Object &obj ) 
{
	int insert_location =0;
	// check if the node is a leaf node. If it is then no need to make it go into subtrees.
	if (leaf())	
	{
		//check if element exists. If so return 0
		for (int i =0; i < num_elements; i++)
		{
			if (elements[i] == obj)
			{
				return 0;
			}
		}
		// check if the node is full, then perform spit and re insert
		// otherwise just insert at appropriate location
		if (full())		
		{
			
			// create a new b_tree_node
			B_tree_node<Object> *temp_node = new B_tree_node<Object> ();
			
			// a bool variable used to check wheter to insert in new node or previous
			bool insert_new = false;
			
			// compare if the new object is grater than middle value
			// if so then copy bottom two values of elements into new node
			// else copy the bottom three elements
			if (obj > elements [2])
			{
				temp_node ->elements[1] = this ->elements[4];
				temp_node ->elements[0] = this ->elements[3];
				temp_node ->num_elements = 2;
				insert_new = true;			
				num_elements = num_elements -2 ;

				// set moved numbers to null
				elements[3] = 0;
				elements[4] = 0;
			}
			else
			{
				temp_node ->elements[0] = this ->elements[2];
				temp_node ->elements[1] = this ->elements[3];
				temp_node ->elements[2] = this ->elements[4];
				temp_node -> num_elements = 3;
				insert_new = false;
				num_elements = 2;

				// set moved numbers to null
				elements[2] = 0;
				elements[3] = 0;
				elements[4] = 0;
			}
			
			//depending on the insert_new flag insert the object
			if (insert_new)
			{
				// go through the temp_node to find where to palce the object
				// insert appropriately
				//temp_node = insert_object(obj,&temp_node
		
				for (int i = (temp_node ->num_elements)-1; i >= -1; i--)
				{
					if (obj < temp_node -> elements[i])
					{
						 temp_node -> elements[i+1] = temp_node -> elements[i];
						// return temp_node;
						//	return i;
					}
					else
					{
						//elements [i+1] = obj;
			
							//return i+1;
						temp_node -> elements [i+1]=obj;
						temp_node ->num_elements++;
						temp_node ->~B_tree_node();
						return temp_node;
					}

					//return temp_node;
				
				}
			}
			else
			{
				insert_location = insert_place(obj);
				elements[insert_location] = obj;
				num_elements++;
				return temp_node;
			}
			
			

		}
		else
		{
			if (empty())
			{
				elements[0] = obj;
				num_elements ++;

			}
			else
			{
				insert_location= insert_place(obj);
				if (insert_location == -1)
				{
					return 0;
				}
				elements[insert_location]=obj; 
				num_elements ++;
				return 0;
			}

		}
	}
	else
	{
		int counter_insertion = 0;
		B_tree_node<Object> *temp = new B_tree_node<Object> ();
		// first lets figure out which node to place the value into
		
		if (obj < elements[1])
		{
			temp = subtrees[0] ->insert(obj);
			counter_insertion = 0;
		// may need to remove
			elements[0] = obj;
		}
		else
		{	
			for (int i = (num_elements - 1) ; i > 0; i--)
			{
				
				if (elements[i] >obj)
				{
					//temp = subtrees[i] -> insert (obj);
					counter_insertion = i;
				}
				else 
				{
					
					temp = subtrees[i] ->insert(obj);
					counter_insertion = i;
					break;
				}
			}
		}
		// check if returned temp is null; if it is then return 0

		if (temp!=0)
		{
			// if the object is full then we need split it by determining where to place 
			if (full())
			{
				
				B_tree_node<Object> *temp_node = new B_tree_node<Object> ();
				temp_node->is_leaf= false;
				// if the insertion place is bigger than 2 then copy the bottom two nodes to the new node
				if (counter_insertion > 2)
				{
					temp_node ->subtrees[0] = this ->subtrees[3];
					temp_node ->subtrees[1] = this ->subtrees[4];
					temp_node ->elements[0] = this ->elements[3];
					temp_node ->elements[1] = this ->elements[4];
					temp_node ->num_elements= 2;	
					// now that the new node is created, find the place to insert it
					
					for (int i = temp_node->num_elements-1; i >= 0; i--)
					{
						if (temp->elements[i] > temp_node ->elements[i] )
						{
							temp_node->subtrees[i+1] = temp;
							temp_node->elements[i+1] = temp->elements[0];
							temp_node ->num_elements++;
							break;
						}
						else
						{
							temp_node ->subtrees[i+1] = temp_node ->subtrees[i];
							temp_node ->elements[i+1] = temp_node ->elements[i];
						}
					}
					this ->num_elements = this->num_elements-2;
					return temp_node;
				}
				else
				{
					// move the 3 largest into the new node and insert into the original
					temp_node ->subtrees[0] = this ->subtrees[2];
					temp_node ->subtrees[1] = this ->subtrees[3];
					temp_node ->subtrees[2] = this ->subtrees[4];

					temp_node ->elements[0] = this ->elements[2];
					temp_node ->elements[1] = this ->elements[3];
					temp_node ->elements[2] = this ->elements[4];
					temp_node ->num_elements= 3;	
					num_elements = num_elements -3;

					for (int i = num_elements-1; i >= 0; i--)
					{
						if (temp->elements[i] > elements[i] )
						{
							subtrees[i+1] = temp;
							elements[i+1] = temp->elements[0];
							num_elements++;
							break;
						}
						else
						{
							subtrees[i+1] = subtrees[i];
							elements[i+1] =elements[i];
						}
					}
				}
				return temp_node;
			}
			
			else
			{
			// if it is not full then move the returned address beside and shift the other arrays
			// then where ever the array was inserted has split into two... the temp must go to the next one
			// the ones after should be swtiched over after that
			// so if the current one is inserted in node 3. then temp would be node 4, and the next one should be node 5
			// or if the current is inserted into the node 1. it means total elements is 4... so 2->3,3->4,4->5, and temp->2
			// the algorightm lookis like.. counter_insertion+2= counter_insertion+1... now if there were 4 to begin with
				
				for (int j = num_elements-1; j >counter_insertion ; --j)
				{
					subtrees[j+1] =subtrees[j];
					elements[j+1] = elements[j];
			
				}
				subtrees[counter_insertion+1] = temp;
				elements[counter_insertion+1] = temp->elements[0];
				num_elements++;
					

					
				return 0;
				
			}
		}	
		
		
	}
	return 0;
}

template <typename Object>
int B_tree_node<Object>::insert_place(const Object  &obj) 
{
//	  use insertion sort to figure out the location to insert at
	for (int i =num_elements-1; i >= -1; i--)
	{
		if (obj == elements[i])
		{
			return -1;
		}
		if (obj < elements[i])
		{
			elements[i+1] = elements[i];
		//	return i;
			
		}
		else
		{
			//elements [i+1] = obj;
			
			return i+1;
		}
	}
	return 0;
}

template <typename Object>
B_tree_node<Object> *B_tree_node<Object>::insert_object( const Object &obj , const B_tree_node<Object> &node)
{
	/* this function inserts the node in the temporary array and then returns the temporary array
	
	 find the place where the object should go*/
	//int node_elements = (node -> (num_elements-1));
	//for (int i = 3; i >= -1; i--)
	//{
	//	if (obj < (node -> elements[i]))
	//	{
	//		node -> elements[i+1] = node -> elements[i];
	//	//	return i;
	//		
	//	}
	//	else
	//	{
	//		//elements [i+1] = obj;
	//		node -> elements[i+1] = obj;
	//		node ->num_elements++;
	//		return node;
	//	}
	//}
	return 0;
}



template <typename Object>
B_tree_node<Object> *B_tree_node<Object>:: find_max(const Object  &obj) 
{
	return 0;
	//return obj;
}

template <typename Object>
void B_tree_node<Object>::draw( int n ) const {
	if ( leaf() ) {
		space( n );
		std::cout << "(" << num_elements << ") ";

		for ( int i = 0; i < num_elements; ++i ) {
			std::cout << elements[i] << " ";
		}

		std::cout << std::endl;
	} else {
		space( n );
		std::cout << "(" << num_elements << ")" << std::endl;
		space( n );
		std::cout << "* -> " << std::endl;
		subtrees[0] -> draw( n + 1 );

		for ( int i = 1; i < num_elements; ++i ) {
			space( n );
			std::cout << elements[i] << "-> " << std::endl;
			subtrees[i] -> draw( n + 1 );
		}
	}
}

template <typename Object>
void B_tree_node<Object>::space( int n ) {
	for ( int i = 0; i < n; ++i ) {
		std::cout << "   ";
	}
}

#endif
