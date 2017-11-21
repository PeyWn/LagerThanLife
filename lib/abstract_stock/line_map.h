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
	*/
	LineMap(string desc);

	/*

	*/
	~LineMap();

	pair<double, double> max_size();
	int get_node_c();
	int get_line_c();
	string make_string();
	stack<Line*> get_path(int i1, int i2);

	LineNode* get_node(int i);
private:
	void add_line(int i1, int i2);
	void add_node(double x, double y);

	vector<LineNode*> nodes;
	vector<Line*> lines;
};
#endif /* LINE_MAP_H */
