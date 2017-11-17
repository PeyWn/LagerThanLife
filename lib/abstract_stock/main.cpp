#include "line_map.h"
#include "line.h"
#include "line_node.h"

using namespace std;

int main(){
    LineNode n0(-7,5, 0);
    LineNode n1(20,5,1);
    LineNode n2(-7,-2, 2);
    LineNode n3(-15, 5, 3);
    LineNode n4(-7,23, 4);

    Line l1(&n0, &n1);
    Line l2(&n0, &n2);
    Line l3(&n0, &n3);
    Line l4(&n0, &n4);

    cout << n0.get_angle(&l3, &l2) << endl;
    cout << n0.get_angle(&l3, &l4) << endl;
    cout << n0.get_angle(&l4, &l3) << endl;
    cout << n0.get_angle(&l4, &l1) << endl;
    cout << n0.get_angle(&l1, &l4) << endl;
    cout << n0.get_angle(&l1, &l2) << endl;
    cout << n0.get_angle(&l2, &l1) << endl;
    cout << n0.get_angle(&l2, &l3) << endl;
}
