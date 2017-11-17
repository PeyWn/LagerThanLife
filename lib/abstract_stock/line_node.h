#ifndef LINE_NODE_H
#define LINE_NODE_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Line;

class LineNode{
	friend class LineMap; //LineMap is friend of LineNode

public:

  	pair<double, double > get_coords();
	int get_angle(Line* start_line, Line* end_line);
	int get_degree();
	bool is_leaf();

private:
	LineNode(double x, double y);
    int id;
	double x;
	double y;
	vector<Line*> lines;
	int degree;

	void add_line(Line* line);
};
#endif /* LINE_NODE_H */
