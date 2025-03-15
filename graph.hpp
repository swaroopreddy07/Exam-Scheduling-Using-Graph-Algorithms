#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "vertex.hpp"
#include "edge.hpp"
#include <bits/stdc++.h>

/****************************************************************************/

// adjacency list class
class adjList {
    edgeList** A;  // Array holding the adjacency edge lists of each vertex
    int size;
public:
    adjList(int);
    void addEdge(int, edge*);
    vertexList* neighbors(int);
};

// adjacency matrix class
class adjMatrix {
    edge*** M;  // 2D Array holding the edge information between vertices
    int size;
public:
    adjMatrix(int);
    void addEdge(edge*);
    vertexList* neighbors(int);
};

/****************************************************************************/

// base class
class graph {
protected:
    int n;
    vertex** VA;  // Keeping an array of vertex objects in all graphs for efficient access
    graph(int n);  // Base class constructor
public:
    // Getter functions

    vertex* getVertex(int);    
    void backTrackScheduling(int, vector<string>&);
    void greedyScheduling(int, vector<string>&);
    void DSATURScheduling(int, vector<string>&);
    void SmallestDegreeLastScheduling(int, vector<string>&);   
    void tabuSearchScheduling(int, vector<string>&);


    virtual void addEdge(int, int) = 0; 
    virtual vertexList* neighbors(vertex*) = 0;
   
};

// derived class of graph
class adjListGraph : public graph {
    adjList* AL;
public:
    // constructor
    adjListGraph(int);
    void addEdge(int, int);
    vertexList* neighbors(vertex*);
    
};

// derived class of graph
class adjMatrixGraph : public graph {
    adjMatrix* AM;
public:
    // constructor
    adjMatrixGraph(int);
    // virtual functions
    void addEdge(int, int);   
    vertexList* neighbors(vertex*);
   
};

class edgeListGraph : public graph {
    edgeList* E;
public:
    // constructor
    edgeListGraph(int);
    // virtual functions
    void addEdge(int source, int dest);  
    vertexList* neighbors(vertex*);
   
};


// Structure to represent the schedule
struct Schedule {
    vector<int> examSlots;
    int conflicts;
};

#endif
