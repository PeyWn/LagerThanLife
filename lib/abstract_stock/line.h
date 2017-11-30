#ifndef LINE_H
#define LINE_H

#include <string>
#include <iostream>
#include "line_node.h"
using namespace std;

class Line{
	friend class LineMap; //LineMap is friend of Line

public:
	/*
	Get end node 0 or 1.

	i - 0 or 1, the end node to get a pointer to.

	return - the end node of given index
	*/
  	LineNode* get_node(int i);

	/*
	Get the length of the line. The euclidean distance between the endnodes.

	return - the length of the line
	*/
	double get_length();

	/*
	Get the node opposite of the given index.

	i - index of one of the lines start nodes

	return - the other end node of the line.
	*/
	LineNode* get_opposite(int i);
private:
	/*
	Create a new Line with the given endnodes.

	n1_in - the first endnode
	n2_in - the second endnode
	*/
	Line(LineNode* n1_in, LineNode* n2_in);

	LineNode* n1 = nullptr;
	LineNode* n2 = nullptr;
	double length = 0;
};

#endif /* LINE_H */
