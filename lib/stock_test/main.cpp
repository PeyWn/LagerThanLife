/*

    **********  TEST FILE FOR ABSTRACT STOCK CLASS **********

*/
#include "../abstract_stock/line_map.h"
#include "../abstract_stock/line.h"
#include "../abstract_stock/line_node.h"
#include "../../UI/text_file_handler.h"
#include <string>
#include <stack>

using namespace std;

int main(){
    string map_folder = "../../maps/";
    string file_name = "big_storage.txt";

    TextFileHandler fh(map_folder);

    string lager = fh.read_text_file(file_name);

    cout << "File read: " << endl;

    LineMap lm(lager);
    stack<Line*> path = lm.get_path(36, 3);

    while(!path.empty()){
        cout << path.top()->get_node(0)->get_id() << " " << path.top()->get_node(1)->get_id() << endl;
        path.pop();
    }
}
