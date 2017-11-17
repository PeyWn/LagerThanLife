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

  	pair<double, double > get_coords();
	int get_angle(Line* start_line, Line* end_line);
	int get_degree();
	bool is_leaf();
	int get_id();
	static double euc_dist(LineNode* n1, LineNode* n2);

	LineNode(double x_in, double y_in, int id_in); //TODO move constructor down to private
private:
    int id;
	double x;
	double y;
	vector<Line*> lines;
	int degree;

	void add_line(Line* line);
};
#endif /* LINE_NODE_H */
