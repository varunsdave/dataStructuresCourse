#ifndef B_TREE_H
#define B_TREE_H

/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "ece250.h"
#include "B_tree_node.h"

template <typename Object>
class B_tree;

template <typename Object>
class B_tree {
	private:
		B_tree_node<Object> *tree_root;

	public:
		B_tree();
		~B_tree();

		B_tree_node<Object> *root() const;
		int        size() const;
		bool       empty() const;
		int        count( Object const & ) const;
		void       draw() const;

		void       insert( Object const & );
};

template <typename Object>
B_tree<Object>::B_tree():tree_root( new B_tree_node<Object>() ) {
	// empty
}

template <typename Object>
B_tree<Object>::~B_tree() 
{
	delete tree_root;
}

template <typename Object>
B_tree_node<Object> *B_tree<Object>::root() const {
	return tree_root;
}

template <typename Object>
bool B_tree<Object>::empty() const {
	return tree_root->empty();
}

template <typename Object>
int B_tree<Object>::size() const {
	return tree_root ->size();
}

template <typename Object>
int B_tree<Object>::count( Object const &obj ) const {
	return tree_root->count(obj);
}

template <typename Object>
void B_tree<Object>::draw() const {
	tree_root -> draw();
}

template <typename Object>
void B_tree<Object>::insert( Object const &obj )
{
	B_tree_node<Object> *temp = tree_root ->insert(obj);
	if (temp !=0)
	{	
		/*if (tree_root -> leaf())
		{*/
			B_tree_node<Object> *node = new B_tree_node<Object> (tree_root, temp);
			tree_root = node;
	
	}
	
}

#endif
