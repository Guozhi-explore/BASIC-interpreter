#ifndef PROGRAM_H
#define PROGRAM_H
#include<map>
#include<string>
#include"statement.h"
class statement;
using namespace std;


class program
{
public:
    program();
    void addOrUpdateSourceCodeLine(int lineNumber,string codeLine);
    void addOrUpdateParsedStatement(int lineNumber,statement *statement);
    int getNextCodeLineNumber(int lineNumber);
    string getLineCode(int lineNumber);
    int getNextStatementLineNumber(int lineNumber);
    statement *getLineStatement(int lineNumber);
    void ListSourceCode();
    void clear();

private:
    map<int, string> sourceCodeArray;
    map<int,statement*> parsedStatementArray;
    map<int,int> nextStatementArray;
};

#endif // PROGRAM_H
