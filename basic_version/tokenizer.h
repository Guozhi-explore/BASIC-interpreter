#include<string>
#include<list>


class Tokenizer{
    private: 
        bool numberCanBeLineIndex;
        int index;
        string input_line;
        list<string> token_list;
    public:
        Tokenizer(string input_line);
        string getToken();
        bool hasMoreToken();
        void saveToken(string token);
}