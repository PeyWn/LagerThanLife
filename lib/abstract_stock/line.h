#include <string.h>
#include <iostream>  
using namespace std;  

class Line{  
	friend class LineMap; 
	
public:  

	//constructor in here somehow
	
    LineNode* get_node(int i);
	double get_lenght(); 
	
private:  
    LineNode* n1;
	LineNode* n2; 
	double length; 
	double euc_dist(LineNode* n1, LineNode* n2);
};  