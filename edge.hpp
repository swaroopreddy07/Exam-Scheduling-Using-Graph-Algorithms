#ifndef EDGE_HPP
#define EDGE_HPP

#include "vertex.hpp"

class edge {
	vertex* source;
	vertex* dest;
public:
	edge(vertex*, vertex*);
	edge(vertex*, vertex*, int);
	vertex* getSource();
	vertex* getDest();
};

class edgeNode {
	edge* e;
	edgeNode* next;
public:
	edgeNode(edge*);
	edge* getEdge();
	edgeNode* getNext();
	void setNext(edgeNode*);
};

class edgeList {
	edgeNode* head;
	int size;
public:
	edgeList();
	edgeNode* getHead();
	void addNode(edgeNode*);
};


#endif
