#include <iostream>
#include "edge.hpp"

edge::edge(vertex* source, vertex* dest) {
	this->source = source;
	this->dest = dest;
}

edge::edge(vertex* source, vertex* dest, int weight) {
	this->source = source;
	this->dest = dest;
}

vertex* edge::getSource() {
	return source;
}

vertex* edge::getDest() {
	return dest;
}

edgeNode::edgeNode(edge* e) {
	this->e = e;
	next = NULL;
}

edge* edgeNode::getEdge() {
	return e;
}

edgeNode* edgeNode::getNext() {
	return this->next;
}

void edgeNode::setNext(edgeNode* node) {
	this->next = node;
}



/**
 * edgeList constructor to create an empty edge list
 */
edgeList::edgeList() {
	head = NULL;
	size = 0;
}

/**
 * get the head of an edgeList
 * @return the head of the edgeList
 */
edgeNode* edgeList::getHead() {
	return head;
}

/**
 * add a new edge node to an edge list (at front)
 * @param node the edge node to be added
 */
void edgeList::addNode(edgeNode* node) {
	node->setNext(head);
	head = node;
	size++;
}
/*********************************************************/

