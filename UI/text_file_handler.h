using namespace std;

class TextFileHandler{
private:
    string map_folder;
public:
    /*
    Construct a TextFileHandler Objext
    */
    TextFileHandler(string map_folder_path);
    string read_text_file(string filename);

};
