#ifndef LINE_NODE_H
#define LINE_NODE_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

//Forward devlare to fix reflexive dependency issue
class Line;

class LineNode{
	friend class LineMap; //LineMap is friend of LineNode

public:
	/*
	Get the coordinates of the node.

	return - the coordinates as a pair where x is first and y second
	*/
	pair<double, double > get_coords();

	/*
	Get the angle between two lines connecting to this node as
	an integer that represents the angle/(pi/2). Only positive angles
	are returned (so for example (-pi/2) is represented as (3pi/2)
	which gives return value 3 from the function). Lines given can not be
	the same (angle 0 rad),

	Examples:
		V
		|
		|
		*---->

	returns 3

	>----*---->

	returns 2

	>----*
	     |
		 |
		 |
		 V

	returns 1

	start_line - the line coming from into the node
	end_line - the destination line to leave the node on

	return - an integer n that represents the positive turn between the lines.
			 To get the turn in rad multiply n with (pi/2).
	*/
	int get_angle(Line* start_line, Line* end_line);

	/*
	Get the degree of the node.

	return - the amount of lines connecting to the node.
	*/
	int get_degree();

	/*
	Check if the node is a leaf, has only one connecting line.

	return - wheather the node is a leaf.
	*/
	bool is_leaf();

	/*
	Get the id of the nodes

	return - the id of the node
	*/
	int get_id();

	/*
	Get the euclidean distance between two nodes.

	n1 - The first node to take the distance from
	n2 - The second node to take the distance from

	return - The euclidean distance between the coordinates of n1 and n2
	*/
	static double euc_dist(LineNode* n1, LineNode* n2);

private:
	/*
	Create a new LineNode object with given id and coordinates.

	x_in - x coordinate for the LineNode
	y_in - y coordinate for the LineNode
	id_in - the id to assign to the LineNode
	*/
	LineNode(double x_in, double y_in, int id_in);

	int id = 0;
	double x = 0;
	double y = 0;
	vector<Line*> lines;
	int degree = 0;

	/*
	Add a line connecting to the node.

	line - the line to add to the node
	*/
	void add_line(Line* line);
};
#endif /* LINE_NODE_H */
