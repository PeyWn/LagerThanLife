#ifndef LINE_H
#define LINE_H

#include <string>
#include <iostream>
#include "line_node.h"
using namespace std;

class Line{
	friend class LineMap; //LineMap is friend of Line

public:

  	LineNode* get_node(int i);
	double get_length();

	Line(LineNode* n1_in, LineNode* n2_in); //TODO move constructor down to private
private:
	LineNode* n1;
	LineNode* n2;
	double length;
};

#endif /* LINE_H */
