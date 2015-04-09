#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <iostream>
#include <limits>
#include "Exception.h"

/*****************************************
 * UW User ID:  
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2011
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

class Weighted_graph {
	private:
		static const double INF;
		int *degree_count ;
		int edge_num;
		double **matrix;
		int verticies;
		// your choice

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double minimum_spanning_tree( int ) const;
		bool is_connected() const;
		void output_prim(bool [], double[], int[]) const;

		void insert( int, int, double );

	// Friends

	friend std::ostream &operator << ( std::ostream &, const Weighted_graph & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph:: Weighted_graph(int n):degree_count (new int [n]),  edge_num(0), matrix(new double *[n]), verticies(n)
{
	/*********************************************************************
	 *  Weighted_graph Constructor
	 *
	 *  Initialize the double array matrix.
	 *  The distance between the edges are set to INF. INF indicates that there is no edge
	 *  Also, initialize the array degree_count which keeps count of the degree each vertex has
	 *  
	 *********************************************************************/
	for (int i =0; i < n; i++)
	{
		matrix[i] = new double [n];
	}

	for (int i =0; i < n; i++)
	{
		for (int j = 0; j<n;j++)
		{
			matrix [i][j] = INF;
		}
		matrix [i][i] = 0;
	}
	for (int i =0; i < n ; i++)
	{
		degree_count [i] = 0;
	}
}
Weighted_graph:: ~Weighted_graph()
{
	/*********************************************************************
	 *  Weighted_graph Destructor
	 *
	 *  Deletes the pointer to the array of matrix
	 *	Once the double pointer is erased it erases the single pointer of the matrix array
	 *  Also, destroys the pointer to memory location for degree_count
	 *  
	 *********************************************************************/
	for (int i =0; i < verticies; i++)
	{
		
		delete[] matrix[i];
		
	}
	delete []matrix;
	delete []degree_count;
}
int Weighted_graph::degree(int n)const
{
	// returns the degree at vertex n, they are stored in array called degree_count
	return degree_count[n];
}
int Weighted_graph::edge_count()const
{
	// returns the number of edges in the graph
	return edge_num;
}
double Weighted_graph::adjacent (int n,int m) const
{
	// check if the arguements are within the limits. Meaning, if n and m 
	// are between 0 and the number of verticies
	if (n >= verticies || m >= verticies || n<0 || m <0)
	{
		throw illegal_argument();
	}
	
	// if n and m are the same it means a vertex is passed in the arguement
	// the distance between the vertex is 0
	// otherwise, if no edge exists then return INF
	// else, return the value at matrix [n][m] which stores the distance of the edge
	if (n == m)
	{
		return 0;
	}
	else if (matrix[n][m] == INF)
	{
		return INF;
	}
	else
	{
		return matrix[n][m];
	}


	
}
double Weighted_graph::minimum_spanning_tree(int m) const
{
	// check if m is a valid input, otherwise throws an illegal_arguement exception
	if (m < 0 || m >= verticies)
	{
		throw illegal_argument();
	}
	// assign local variables
	
	bool completed_graph = true;	//checks if graph is complete
	bool *visited = new bool [verticies]; //array to check if a vertex has been visited
	double *distance = new double [verticies]; // array to store the minimum distance to the vertex
	int *parent = new int [verticies];	// array stores the parent node
	
	// set the table for prim's algorithm by setting visited of all nodes to false
	// the distance as infinity and the parent to be -1
	for (int i = 0; i < verticies ; i++)
	{
		visited [i] = false;
		distance [i] = INF;
		parent [i] = -1;
	}

	//set the root node at m
	distance[m] = -1;
	parent[m] = -1;
	// initialization completed
	bool continue_loop = false;
	int next_node_to_visit = m;
	// set the current starting node to m and set it as a root node
	int current_node =m;
	visited[m] = true;
	distance [m] = 0;
	parent [m] = -1;
	// go through the table
	do
	{
		int counter =0;
		double current_low = INF;
		current_node = next_node_to_visit;
		visited[current_node]= true;

		// update the table to find the edges
		// iterate through the table n times, n is the number of verticies
		// update its parent and distance parameters of the vertex only if 
		// it has not been visited and the distance between the current node
		// and i is less that the value already stored
		for (int i =0; i < verticies; i++)
		{
			if (!visited[i])
			{
				double test = adjacent (current_node,i);
				if (adjacent(current_node,i)!=INF &&test!= 0.0 )
				{					
					if (test < distance[i])
					{
						parent[i] = current_node;
						distance[i] = test;
					}
				}
			}
		}
		
		// find the next node to visit
		// iterate through the table of distances to find the lowest value
		// this value will be set to visit the next node;
		for (int i =0 ; i < verticies; i++)
		{
			if (!visited[i])
			{
				if (distance[i]!= INF)
				{
					if (distance[i]<current_low)
					{
						next_node_to_visit = i;
						current_low = distance [i];
					}
				}
			}
			
		}

		//find if graph is completed or if it a a minimum spanning tree
		for (int i =0; i < verticies; i++)
		{
			if (distance[i] == INF)
			{
				completed_graph = false; // it is a minimum spanning true
			}
		}

		double sum = 0;
		// check if all the nodes have been visited and their distance is not infinity
		// if the graph is completed then it is ready to return the sum
		// iterates through the table and adds the sum of the table and retuns the value
		// before returning the pointers are deleted to free the memory
		if (completed_graph)
		{
			for(int i =0; i < verticies; i++)
			{
				if (distance[i]!=INF && visited[i]==true)
				{
					counter ++;
					sum = sum + distance[i];
				}
				if (counter == verticies)
				{
					// this means it is a full spanning tree hence return the sum of the distances
						//delete the tables
					delete [] visited;
					delete [] distance;
					delete [] parent;
					return sum;
				}
			}
		}
			
		// now check whether or not to continue the loop.
		// assume visit is false
		continue_loop = false;
		// find out if the loop has to be continued
		for (int i =0; i < verticies; ++i)
		{
			if (!visited[i] && distance[i] != INF)
			{
				continue_loop = true;
			}
		}
		
//output_prim (visited, distance, parent);
//	std::cout << current_node << std::endl;
	}
	while (continue_loop);
//	output_prim(visited, distance, parent);
	if (!completed_graph)
	{
		double sum =0;
		for (int i =0; i < verticies; i++)
		{
			if (distance[i] < INF && visited[i])
			{
				sum = sum+distance[i];
			}
		}

		//delete the tables
		delete [] visited;
		delete [] distance;
		delete [] parent;
		return sum;
	}
//	return 0.0;
}
void Weighted_graph::output_prim(bool visited[] , double distance [] , int parent []) const
{
	std::cout << std::endl;
	for (int i =0; i < verticies; i++)
	{
		std::cout << i << "    "<<visited[i] << "    "<< distance[i]<< "    " <<parent[i]<<std::endl;
	} 
}
bool Weighted_graph::is_connected() const
{
	//initialization
	bool *visited = new bool [verticies];//array to check if a vertex has been visited
	double *distance = new double [verticies];// array to store the minimum distance to the vertex
	int *parent = new int [verticies];// array stores the parent node
	
	
	// set the table for prim's algorithm by setting visited of all nodes to false
	// the distance as infinity and the parent to be -1
	for (int i = 0; i < verticies ; i++)
	{
		visited [i] = false;
		distance [i] = INF;
		parent [i] = -1;
	}
	distance[0] = -1;
	parent[0] = -1;
	// initialization completed
	bool continue_loop = false;
	int next_node_to_visit = 0;

	int current_node =0;
	// go through the table

	visited[0] = true;
	distance [0] = 0;
	parent [0] = -1;
	// update the table to find the edges
	// iterate through the table n times, n is the number of verticies
	// update its parent and distance parameters of the vertex only if 
	// it has not been visited and the distance between the current node
	// and i is less that the value already stored
	do
	{
		int counter =0;
		double current_low = INF;
		current_node = next_node_to_visit;
		visited[current_node]= true;
		// update the table to find the edges
		for (int i =0; i < verticies; i++)
		{
			if (!visited[i])
			{
				double test = adjacent (current_node,i);
				if (adjacent(current_node,i)!=INF &&test!= 0.0 )
				{
					if (test < distance[i])
					{
						parent[i] = current_node;
						distance[i] = test;
					}
				}
			}
		}
		// find the next node to visit
		for (int i =0 ; i < verticies; i++)
		{
			if (!visited[i])
			{
				if (distance[i]!= INF)
				{
					if (distance[i]<current_low)
					{
						next_node_to_visit = i;
						current_low = adjacent(current_node,i);
					}
				}
			}
			
		}
		
		// check if all the nodes have been visited and their distance is not infinity
		for(int i =0; i < verticies; i++)
		{
			if (distance[i]!=INF && visited[i]==true)
			{
				counter ++;
			}
			if (counter == verticies)
			{
					//delete the tables
					delete [] visited;
					delete [] distance;
					delete [] parent;
				return true;
			}
		}
			
		// now check whether or not to continue the loop.
		// assume visit is false
		continue_loop = false;
		for (int i =0; i < verticies; ++i)
		{
			if (!visited[i] && distance[i] != INF)
			{
				continue_loop = true;
			}
		}

	
	}
	while (continue_loop);
		//delete the tables
					delete [] visited;
					delete [] distance;
					delete [] parent;
	return false;
	
}
void Weighted_graph::insert (int n, int m, double w)
{
	// if a vertex is passed then an illegal arguement is thrown
	// if an invalid arguement is passed then illegal arguement is throws
	if (m == n)
	{
		throw illegal_argument();
	}
	if (n >= verticies || n < 0 || m >= verticies || m < 0)
	{
		throw illegal_argument();
	}

	if (w<0 || w==INF)
	{
		throw illegal_argument();
	}
	// if the distance between an edge it 0 it has to be removed. 
	// first checks if an edge exists, if it does only then it is removed
	else if (w == 0)
	{
		if (matrix [n][m] != INF || matrix[m][n] !=INF)
		{
			matrix [n][m] = matrix [m][n] = INF;
			
			degree_count [m] --;
			degree_count [n]--;
			edge_num --;
		}
		
	}
	// if an edge already exist then just insert without increasing the count
	else if (adjacent (m,n) != INF )
	{
		matrix [n][m] = w;
		matrix [m][n] = w;
	}
	else
	{
		// insert at matrix and increase the degree count as well as edge count
		matrix [n][m] = w;
		matrix [m][n] = w;
		edge_num++;
		degree_count [m]++;
		degree_count [n]++;
	}
	
}
std::ostream &operator << ( std::ostream &out, const Weighted_graph &WG ) {
	out<<std::endl;
	for (int i =0 ; i< WG.verticies; i++)
	{
		for (int j=0; j<WG.verticies;j++)
		{
			if (WG.matrix[i][j] == WG.INF)
			{
				out << "inf    ";

			}
			else
			{

				out << WG.matrix[i][j] << "      ";
			}
		}
		out << std::endl ;
	}
	return out;
}
#endif
