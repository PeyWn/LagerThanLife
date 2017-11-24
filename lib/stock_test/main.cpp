/*

    **********  TEST FILE FOR ABSTRACT STOCK CLASS **********

*/
#include "../abstract_stock/line_map.h"
#include "../abstract_stock/line.h"
#include "../abstract_stock/line_node.h"
#include <string>
#include <stack>

using namespace std;

int main(){
    string lager = "16 "
    "17 "
    "0 0 "
    "0 90 "
    "47 90 "
    "47 58 "
    "131 33 "
    "131 0 "
    "168 0 "
    "168 33 "
    "196 33 "
    "168 90 "
    "236 90 "
    "236 69 "
    "274 0 "
    "274 45 "
    "274 90 "
    "374 45 "
    "0 1 "
    "0 5 "
    "1 2 "
    "2 3 "
    "2 9 "
    "4 5 "
    "5 6 "
    "6 7 "
    "6 12 "
    "7 8 "
    "7 9 "
    "9 10 "
    "10 11 "
    "10 14 "
    "12 13 "
    "13 14 "
    "13 15 ";

    LineMap a(lager);
    stack<Line*> path = a.get_path(3, 8);

    while(!path.empty()){
        cout << path.top()->get_node(0)->get_id() << " " << path.top()->get_node(1)->get_id() << endl;
        path.pop();
    }
}
