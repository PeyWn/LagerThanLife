#include "line.h"

Line::Line(LineNode* n1_in, LineNode* n2_in) : n1(n1_in), n2(n2_in){
    length = LineNode::euc_dist(n1, n2);
}

LineNode* Line::get_node(int i){
    if(i == 0){
        return n1;
    }
    else{
        return n2;
    }
}


double Line::get_length(){
    return length;
}
