#include <iostream>
#include <fstream>
#include "text_file_handler.h"

TextFileHandler::TextFileHandler(){}

string TextFileHandler::read_text_file(string filename){

    string str;
    string strTotal = " ";
    string myfile = ("../maps/" + filename);
    ifstream in;

    in.open(myfile);
    getline(in,str);

    while ( in ) {
       strTotal += str + " ";
       getline(in,str);
    }

    return strTotal;

}
