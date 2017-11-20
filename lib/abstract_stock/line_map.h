#ifndef LINE_MAP_H
#define LINE_MAP_H

#include <string>
#include <queue>
#include <iostream>
#include <vector>

#include "line.h"
#include "line_node.h"
using namespace std;

class LineMap{

public:
	LineMap(string desc);
	~LineMap();

	pair<double, double> max_size();
	int get_node_c();
	int get_line_c();
	string make_string();
	queue<Line*> get_path(int i1, int i2);

	LineNode* get_node(int i);
private:
	void add_line(int i1, int i2);
	void add_node(double x, double y);

	vector<LineNode*> nodes;
	vector<Line*> lines;
};
#endif /* LINE_MAP_H */
