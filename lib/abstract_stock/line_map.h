#ifndef LINE_MAP_H
#define LINE_MAP_H

#include <string>
#include <queue>
#include <iostream>
#include "line.h"
#include "line_node.h"
using namespace std;

class LineMap{

public:

	LineMap(string desc);

	pair<double, double> max_size();
	int nodes();
	int edges();
	string make_string();
	queue<Line*> get_path(int i1, int i2);
	LineNode* get_node(int i);

private:
	void add_line(int n1, int n2);
	void add_node(double x, double y);

};
#endif /* LINE_MAP_H */
