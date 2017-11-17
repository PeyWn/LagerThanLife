#ifndef LINE_H
#define LINE_H

#include <string>
#include <iostream>
#include "line_node.h"
using namespace std;

class Line{
	friend class LineMap; //LineMap is friend of Line

public:
	Line(LineNode* n1, LineNode* n2);

  	LineNode* get_node(int i);
	double get_lenght();

private:
	LineNode* n1;
	LineNode* n2;
	double length;
	double euc_dist(LineNode* n1, LineNode* n2);
};

#endif /* LINE_H */
