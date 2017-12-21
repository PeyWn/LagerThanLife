using namespace std;

class TextFileHandler{
private:
    string map_folder;
public:
    /*
    Construct a TextFileHandler Objext
    */
    TextFileHandler(string map_folder_path);

    /*
    Reads a text file and creates a string representation of it's content.
    Used for reading lager files.

    string filename - the path to the file that we want to read

    return - returns a string containing the content of the file "filename"
    */
    string read_text_file(string filename);

};
