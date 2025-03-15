/*********************** COMPLETE THE FUNCTIONS AS INSTRUCTED ****************************/
/*********************** DO NOT INCLUDE ANY MORE HEADER FILES ****************************/

#include <iostream>
#include "graph.hpp"

#include <bits/stdc++.h>
/************************************************************************************/


/************************************************************************************/


/**
 * get the neighbors of a vertex
 * @param id the vertex label
 * @return the vertex list of the neighbors of the vertex
 */
vertexList* adjList::neighbors(int id) {
	vertexList* N = new vertexList();
	edgeList* a= A[id];
	edgeNode* temp=a->getHead();
	while(temp!=nullptr){
    N->addNode(new vertexNode(temp->getEdge()->getDest()));
     temp=temp->getNext();
	}
  return N;
}



/**
 * get the neighbors of a vertex
 * @param v the vertex
 * @return the vertex list of the neighbors of the vertex
 */
vertexList* adjListGraph::neighbors(vertex* v) {
	return AL->neighbors(v->getId());	
}



/************************************************************************************/

/**
 * get the neighbors of a vertex
 * @param id the vertex label
 * @return the vertex list of the neighbors of the vertex
 */
vertexList* adjMatrix::neighbors(int id) {
	vertexList* N = new vertexList();
	for(int j=0;j<size;j++){
		if(M[id][j]!=nullptr)
		N->addNode(new vertexNode(M[id][j]->getDest()));
	}	
	return N;
}

/**
 * get the neighbors of a vertex
 * @param v the vertex
 * @return the vertex list of the neighbors of the vertex
 */
vertexList* adjMatrixGraph::neighbors(vertex* v) {
	return AM->neighbors(v->getId());
}




/************************************************************************************/


// Function to get the neighbors of a vertex in an edgeList graph
vertexList* edgeListGraph::neighbors(vertex* v) {
    vertexList* N = new vertexList();  // List of neighboring vertices
    edgeNode* temp = E->getHead();     // Start with the first edge in the edge list

    // Iterate through all the edges in the edge list
    while (temp != nullptr) {
        edge* e = temp->getEdge();

        // Check if the source or destination is the given vertex
        if (e->getSource() == v) {
            N->addNode(new vertexNode(e->getDest()));  // Add the destination vertex to neighbors
        } else if (e->getDest() == v) {
            N->addNode(new vertexNode(e->getSource()));  // Add the source vertex to neighbors
        }

        temp = temp->getNext();  // Move to the next edge
    }

    return N;  // Return the list of neighbors
}

