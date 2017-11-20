/*

    **********  TEST FILE FOR ABSTRACT STOCK CLASS **********

*/


#include "line_map.h"
#include "line.h"
#include "line_node.h"
#include <string>

using namespace std;

int main(){
    string lager = "8 "
        "7 "
        "5 2 "
        "5.5 8 "
        "11 8 "
        "11 0 "
        "0 0 "
        "0 5 "
        "7 5 "
        "7 2 "
        "1 2 "
        "2 3 "
        "3 4 "
        "4 5 "
        "5 6 "
        "6 7 "
        "7 0 ";

    LineMap a(lager);
    cout << a.make_string() << endl;
}
