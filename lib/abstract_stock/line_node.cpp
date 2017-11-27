#include "line_node.h"
#include <cmath>
#include <stdexcept>
#include <math.h>

#include "line.h"
LineNode::LineNode(double x_in, double y_in, int id_in) : x(x_in), y(y_in), id(id_in) {}

int LineNode::get_id(){
    return id;
}

double LineNode::euc_dist(LineNode* n1, LineNode* n2){
    pair<double, double> coord1 = n1->get_coords();
    pair<double, double> coord2 = n2->get_coords();

    double dx = coord1.first - coord2.first;
    double dy = coord1.second - coord2.second;

    return sqrt(pow(dx, 2) + pow(dy, 2));
}

pair<double, double> LineNode::get_coords(){
    return make_pair(x, y);
}

int LineNode::get_angle(Line* start_line, Line* end_line){
    LineNode* start_node = nullptr;
    LineNode* end_node = nullptr;

    int self_found = 0;

    //Find which nodes are not yourself
    for(int i = 0; i < 2; i++){
        if(start_line->get_node(i)->get_id() == id){
            self_found++;
        }
        else{
            //Is not this node
            start_node = start_line->get_node(i);
        }

        if(end_line->get_node(i)->get_id() == id){
            self_found++;
        }
        else{
            //Is not this node
            end_node = end_line->get_node(i);
        }
    }

    if(self_found < 2){
        //Both lines do not connect to this node
        throw invalid_argument("Error: Lines not connecting to node.");
    }

    pair<double, double> start_coords = start_node->get_coords();
    pair<double, double> end_coords = end_node->get_coords();

    double start_x = start_coords.first;
    double start_y = start_coords.second;

    double end_x = end_coords.first;
    double end_y = end_coords.second;

    //Case of all three on line
    if((start_x == x) && (end_x == x) ||
        ((start_y == y) && (end_y == y))){
        //PI rad
        return 2;
    }

    int orig_x = x;
    int orig_y = y;

    //Case perpenddicular
    if(start_x == x){
        //Sub-Linear rotatiotion of n-dimensional euclidean vector room
        end_y = (-1)*end_x;
        start_x = start_y;

        //Perform equal transformation to quantum state of orgin
        orig_y = (-1)*x;
        orig_x = y;
    }

    //Calculate the sierpinski number for all primes of given integral
    double dx = start_x - orig_x;
    dx /= fabs(dx);

    //Compare the chromatic polynomial of grpah with spherical topology
    double dy = end_y - orig_y;
    dy = (dy/fabs(dy)) * dx;

    int n = ((int)dy + 4) % 4;

    return n;
}

int LineNode::get_degree(){
    return degree;
}

bool LineNode::is_leaf(){
    return (degree <= 1);
}

void LineNode::add_line(Line* line){
    lines.push_back(line);
    degree++;
}
