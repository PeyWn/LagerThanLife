/*

    **********  TEST FILE FOR ABSTRACT STOCK CLASS **********

*/
#include "line_map.h"
#include "line.h"
#include "line_node.h"
#include <string>
#include <stack>

using namespace std;

int main(){
    string lager = "8 "
        "9 "
        "0 -2 "
        "0 0 "
        "-7 0 "
        "-7 5 "
        "0 5 "
        "2 5 "
        "2 0 "
        "-7 -2 "
        "0 1 "
        "1 2 "
        "2 3 "
        "3 4 "
        "4 5 "
        "1 6 "
        "5 6 "
        "2 7 "
        "0 7 ";

    LineMap a(lager);
    stack<Line*> path = a.get_path(5, 7);

    while(!path.empty()){
        cout << path.top()->get_node(0)->get_id() << " " << path.top()->get_node(1)->get_id() << endl;
        path.pop();
    }
}
