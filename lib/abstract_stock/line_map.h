#ifndef LINE_MAP_H
#define LINE_MAP_H

#include <string>
#include <stack>
#include <iostream>
#include <vector>

#include "line.h"
#include "line_node.h"
using namespace std;

class LineMap{

public:
	/*
	Create a new LineMap based on the given string. Sets up all nodes and lines.

	desc - String describing the map according to standard:

	node_count	(n)
	line_count	(m)
	x1 y1
	x2 y2
	...
	xn yn
	i1_1 i2_1
	i1_2 i2_2
	...
	i1_m i2_m
	*/
	LineMap(string desc);

	/*
	Destructor for LineMap class.
	Unallocates all dynamically allocated memory for LineNodes and Lines.
	*/
	~LineMap();

	/*
	Get the max rectangular size the storage will take up in the physical world.

	return - a pair of width and height that the storage will take up.
	 		The width is max difference between two x-coordinates in the map.
			The height is max difference between two y-coordinates in the map.
	*/
	pair<double, double> max_size();

	/*
	Get the amount of nodes in the map.

	return - the amount of nodes stored in the map
	*/
	int get_node_c();

	/*
	Get the amount of lines in the map.

	return - the amount of lines stored in the map.
	*/
	int get_line_c();

	/*
	Serialize the map structure into a string following the same format
	as the constructor of this class.

	return - the complete string describing the map.
			Does not use newlines to separate data, only spaces-
	*/
	string make_string();

	/*
	Get the shortest path between two nodes in the map.
	Uses dijkstras shortest path algorithm.

	i1 - index of the start node to find the path from
	i2 - index of the end node to find the path to

	return - A stack of Line-pointers. Starting from the start node
			the lines in the path to the end node will be in the stack
			from up to down. Note that the end nodes of the lines are not in
			any specific order, so in order to find the next node in the path
			the two end nodes would have to be compared to the last node in
			the path to find which of them is the new one.
	*/
	stack<Line*> get_path(int i1, int i2);

	/*
	Get a pointer to the node with index i

	i - index of the node to get

	return - a pointer to the LineNode that has the given index.
	*/
	LineNode* get_node(int i);
private:
	/*
	Add a line to the map between the given indexes.

	i1 - index of the first endnode of the new line.
	i2 - index of the second endnode of the new line.
	*/
	void add_line(int i1, int i2);

	/*
	Add a node to the map at the given coordinates.

	x - the x-coordinate of the new node
	y - the x-coordinate of the new node
	*/
	void add_node(double x, double y);

	vector<LineNode*> nodes;
	vector<Line*> lines;
};
#endif /* LINE_MAP_H */
