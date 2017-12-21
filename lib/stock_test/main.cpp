/*
    **********  TEST FILE FOR ABSTRACT STOCK CLASS **********
*/
#include "../abstract_stock/line_map.h"
#include "../abstract_stock/line.h"
#include "../abstract_stock/line_node.h"
#include "../../UI/text_file_handler.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
    string map_folder = "../../maps/";
    string file_name = "big";

    TextFileHandler fh(map_folder);

    string lager = fh.read_text_file(file_name);

    cout << "File read: " << endl;

    LineMap lm(lager);

    for(int i = 0; i < lm.get_node_c(); ++i){
        cout << "degree " << i << ": " << lm.get_node(i)->get_degree() << endl;
    }
}
