#include <string.h>
#include <iostream>  
using namespace std;  

class LineNode{  
	friend class LineMap; 
	
public:  

	//constructor in here somehow
	
    pair<double x, double y> get_coords();
	int get_angle(Line* start_line, end_line Line*); 
	int get_degree();
	bool is_leaf(); 
	
private:  
    int id; 
	double x;
	double y;
	vector<Line*>;
	int degree; 
	
	void add_line(Line);
};  