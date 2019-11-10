#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include<queue>
#include<vector>
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
        string input_line;
        vector<Token> token_list;
        //提前查看的token被返回到此处
        queue<Token> return_token;

        void addNewSymbol(string token_string);
        void parseInputLineToTokenList();
        bool alphabetAndDigit(char s);
        bool isOperator(char s);
        void addIdOrReserveOrNumber(string token_string);
        bool isReserveToken(string token_string);
    public:
        Tokenizer(string input_line);
        Token getToken();
        bool hasMoreToken();
        void saveToken(Token token);
};



#endif // TOKENIZER_H
