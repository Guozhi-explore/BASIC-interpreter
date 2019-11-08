#include <string>
#include<queue>
using namespace std;

class Tokenizer{
    public:
    enum tokenType {RESERVE,ID,STRING,NUMBER,OPERATOR,ERROR,NONE,};
    struct Token
    {
        /* data */
        tokenType token_type;
        string token_string;
        Token(){
            this->token_type=NONE;
            token_string="";
        }
    };
    
    private: 
        bool numberCanBeLineIndex;  
        bool ignoreBlankFlag;
        int index;
        string input_line;
        queue<Token> token_list;

        void addNewSymbol(string token_string);
        void parseInputLineToTokenList();
        bool alphabetAndDigit(char s);
        bool isOperator(char s);
        void addIdOrReserve(string token_string);
        bool isReserveToken(string token_string);
    public:
        Tokenizer(string input_line);
        Token getToken();
        bool hasMoreToken();
        void saveToken(Token token);
};

