#include "line.h"
#include <stdexcept>

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

LineNode* Line::get_opposite(int i){
    if(n1->get_id() == i){
        return n2;
    }
    else if(n2->get_id() == i){
        return n1;
    }
    else{
        //Given id not one of the endnodes
        throw invalid_argument("Error: Index not one of the end nodes.");
    }
}
