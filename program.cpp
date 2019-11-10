#include "program.h"
#include "assert.h"
#include"error.h"

program::program()
{

}

void program::addOrUpdateSourceCodeLine(int lineNumber, string codeLine)
{
    sourceCodeArray[lineNumber]=codeLine;
}

void program::addOrUpdateParsedStatement(int lineNumber, statement *statement)
{
    parsedStatementArray[lineNumber]=statement;
}

void program::ListSourceCode(Console &console)
{
    map<int,string>::iterator iterator;
    iterator=sourceCodeArray.begin();
    while(iterator!=sourceCodeArray.end())
    {
        console.writePrintMsg(iterator->second);
        //printToConsole(iterator->second);
        iterator++;
    }
}

bool program::hasLineNumberInSourceCode(int lineNumber)
{
    return this->sourceCodeArray.find(lineNumber)!=sourceCodeArray.end();
}

void program::deleteLine(int lineNumber)
{
    this->sourceCodeArray.erase(lineNumber);
    this->parsedStatementArray.erase(lineNumber);
}

void program::clear()
{
    this->sourceCodeArray.clear();
    this->nextStatementArray.clear();
    this->parsedStatementArray.clear();
}

void program::run(Console &console)
{
    this->nextStatementArray.clear();
    this->state.clear();
    int lineNumber;
    if(parsedStatementArray.empty())
        return;
    map<int,statement*>::iterator iter=parsedStatementArray.begin();
    lineNumber=iter->first;
    /*init nextStatementArray as the lineNumber order*/
    while(iter!=parsedStatementArray.end())
    {
        int line=iter->first;
        nextStatementArray[line]=-1;
        iter++;
        if(iter!=parsedStatementArray.end())
            nextStatementArray[line]=iter->first;
    }

    do{
        if(parsedStatementArray.find(lineNumber)==parsedStatementArray.end())
        {
            error("jump to line which not declared,aborted");
            return;
        }
        //REM expression return nullptr when parsing
        if(parsedStatementArray[lineNumber]!=nullptr)
        {
            //execute process may change nextlinenumber
            parsedStatementArray[lineNumber]->execute(state,nextStatementArray,lineNumber,console);
        }
        lineNumber=nextStatementArray[lineNumber];
    }
    // lineNumber is set to -1 in the end statement
    while(lineNumber!=-1);
}
