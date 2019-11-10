#ifndef PROGRAM_H
#define PROGRAM_H
#include<map>
#include<string>
#include"statement.h"
#include"evalstate.h"
class evalstate;
class statement;
using namespace std;


class program
{
public:
    program();
    void addOrUpdateSourceCodeLine(int lineNumber,string codeLine);
    void addOrUpdateParsedStatement(int lineNumber,statement *statement);
    bool hasLineNumberInSourceCode(int lineNumber);
    void deleteLine(int lineNUmber);
    void ListSourceCode();
    void clear();
    void run(Console &console);

private:
    map<int, string> sourceCodeArray;
    map<int,statement*> parsedStatementArray;
    map<int,int> nextStatementArray;
    evalstate state;
};

#endif // PROGRAM_H
