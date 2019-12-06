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
    void ListSourceCode(Console &console);
    void clear();
    void run(Console &console);
    void rerun(Console &console);

private:
    //source code for LIST statement
    map<int, string> sourceCodeArray;
    //parsed statement array for RUN statement
    map<int,statement*> parsedStatementArray;
    //next jump line number ,as STATEMENT like GOTO & IF will change next jump line
    map<int,int> nextStatementArray;
    //store variable's value in the run process
    evalstate state;
    int currentLine;
};

#endif // PROGRAM_H
