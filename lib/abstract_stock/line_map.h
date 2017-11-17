#include <string.h>
#include <iostream>
using namespace std;

class LineMap{

public:

	//constructor in here somehow

	pair<double x, double y> max_size(); 
	int nodes();
	int edges();
	string make_string();
	queue<Line*> get_path(int i1, int i2);
	LineNode* get_node(int i);

private:
    void add_line(int n1, int n2);
	void add_node(double x, double y);

};
