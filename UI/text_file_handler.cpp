#include <iostream>
#include <fstream>
#include "text_file_handler.h"

TextFileHandler::TextFileHandler(string map_folder_path):
    map_folder(map_folder_path){}

string TextFileHandler::read_text_file(string filename){

    string str;
    string strTotal = " ";
    string myfile = (map_folder + filename);
    ifstream in;

    in.open(myfile);
    getline(in,str);

    while ( in ) {
       strTotal += str + " ";
       getline(in,str);
    }

    return strTotal;

}
