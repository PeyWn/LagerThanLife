#include <stdexcept>
#include <sstream>
#include <iostream>
#include <functional>

#include "line_map.h"

LineMap::LineMap(string desc){
    //Prepare stringstream with whole LineMap description
    stringstream ss;
    ss << desc;

    //Tell stringstream to throw eof, fial and bad exceptions

    ss.exceptions(stringstream::failbit
                | stringstream::eofbit
                | stringstream::badbit);

    int node_c, line_c;

    //Read amount of nodes and edges
    ss >> node_c;
    ss >> line_c;

    double x_in, y_in;
    //Read nodes
    for(int i = 0; i < node_c; ++i){
        ss >> x_in;
        ss >> y_in;

        add_node(x_in, y_in);
    }

    //Read lines
    int i1, i2;
    for(int i = 0; i < line_c; ++i){
        ss >> i1;
        ss >> i2;

        if(i1 >= node_c || i2 >= node_c || i1 == i2){
            //Invalid end node indexes
            throw invalid_argument(string("Invalid end node indexes: ") +
                                to_string(i1) + string(" ") + to_string(i2));
        }

        add_line(i1, i2);
    }
}

LineMap::~LineMap(){

}

pair<double, double> LineMap::max_size(){
    int node_c = get_node_c();
    //Empty graph or 1 node
    if(node_c < 2){
        return make_pair(0,0);

    }
    LineNode* node_one = nodes.at(0);

    double min_x = node_one->x;
    double max_x = node_one->x;
    double min_y = node_one->y;
    double max_y = node_one->y;

    LineNode* curNode;
    for(int i = 1; i < node_c; ++i){
        curNode = nodes.at(i);

        min_x = min(min_x, curNode->x);
        max_x = max(max_x, curNode->x);

        min_y = min(min_y, curNode->y);
        max_y = max(max_y, curNode->y);
    }

    double delta_x = max_x - min_x;
    double delta_y = max_y - min_y;

    return make_pair(delta_x, delta_y);
}

int LineMap::get_node_c(){
    return nodes.size();
}

int LineMap::get_line_c(){
    return lines.size();
}

string LineMap::make_string(){
    stringstream ss;

    //Add nde and line count
    ss << get_node_c() << " ";
    ss << get_line_c() << " ";

    //Add nodes
    for(LineNode* node : nodes){
        ss << node-> x << " " << node->y << " ";
    }

    //Add edges
    for(Line* line : lines){
        ss << line->n1->id << " " << line->n2->id << " ";
    }

    return ss.str();
}

queue<Line*> LineMap::get_path(int i1, int i2){
    int node_c = get_node_c();

    if(i1 >= node_c || i2 >= node_c || i1 == i2){
        //Invalid node indexes
        throw invalid_argument(string("Invalid node indexes: ") +
                            to_string(i1) + string(" ") + to_string(i2));
    }

    //Dijkstras algorithm
    vector<int> prev(node_c,0); //Id of previous node
    vector<int> cost(node_c,0); //Cost for every node
    vector<bool> visited(node_c, false); //Whether the node has been visited

    //Function for ordering priority queue
    function<bool(LineNode*, LineNode*)> compare =
        [&](LineNode* n1, LineNode* n2){
            return cost.at(n1->id) > cost.at(n2->id);
        };

    priority_queue<LineNode*,
                vector<LineNode*>,
                function<bool(LineNode*, LineNode*)> > que(compare);

    //First search node
    LineNode* start = get_node(i1);
    LineNode* cur = start;

    //loop until end node hit
    while(cur->id != i2){

        //look at all neighbors
        LineNode* new_neighbor;
        int neighbor_id;
        double newDist;
        for(Line* neighbor_line : cur->lines){
            //Find out which endpoint is neighbor
            if(neighbor_line->n1->id == cur->id){
                new_neighbor = neighbor_line->n2;
            }
            else{
                new_neighbor = neighbor_line->n1;
            }

            newDist = cost.at(new_neighbor->id);

            //See if we want to update neighbor
            
        }

        //Update current node
        cur = que.top();
        que.pop();
    }
}

LineNode* LineMap::get_node(int i){
    return nodes.at(i);
}

void LineMap::add_line(int i1, int i2){
    LineNode* n1 = get_node(i1);
    LineNode* n2 = get_node(i2);

    Line* new_line = new Line(n1, n2);
    n1->add_line(new_line);
    n2->add_line(new_line);

    lines.push_back(new_line);
}

void LineMap::add_node(double x, double y){
    int new_id = get_node_c(); //Length if index of new node (last-index + 1)
    LineNode* new_node = new LineNode(x, y, new_id);

    nodes.push_back(new_node);
}
