#include "program.h"
#include "assert.h"


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

void program::ListSourceCode()
{
    map<int,string>::iterator iterator;
    iterator=sourceCodeArray.begin();
    while(iterator!=sourceCodeArray.end())
    {
        printf("%s\n",iterator->second.c_str());
        iterator++;
    }
}

int program::getNextStatementLineNumber(int lineNumber)
{
    assert(this->nextStatementArray.find(lineNumber)!=nextStatementArray.end());
    return this->nextStatementArray.at(lineNumber);
}

statement *program::getLineStatement(int lineNumber)
{
    assert(this->parsedStatementArray.find(lineNumber)!=this->parsedStatementArray.end());
    return this->parsedStatementArray.at(lineNumber);
}

void program::clear()
{
    this->sourceCodeArray.clear();
    this->nextStatementArray.clear();
    this->parsedStatementArray.clear();
}

void program::run()
{
    int lineNumber;
    if(sourceCodeArray.empty())
        return;
    map<int,string>::iterator iter=sourceCodeArray.begin();
    lineNumber=iter->first;
    /*init nextStatementArray as the lineNumber order*/
    while(iter!=sourceCodeArray.end())
    {
        int line=iter->first;
        nextStatementArray[line]=-1;
        iter++;
        if(iter!=sourceCodeArray.end())
            nextStatementArray[line]=iter->first;
    }

    do{
        printf("line: %d\n",lineNumber);
        if(parsedStatementArray.find(lineNumber)==parsedStatementArray.end())
        {
            printf("jump to line which not declared,aborted\n");
            return;
        }
        parsedStatementArray[lineNumber]->execute(state,nextStatementArray);
        lineNumber=nextStatementArray[lineNumber];
    }
    // lineNumber is set to -1 in the end statement
    while(lineNumber!=-1);
}
