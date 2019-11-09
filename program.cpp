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
            printf("jump to line which not declared,aborted\n");
            return;
        }
        //REM expression return nullptr when parsing
        if(parsedStatementArray[lineNumber]!=nullptr)
        {
            parsedStatementArray[lineNumber]->execute(state,nextStatementArray,lineNumber);
        }
        lineNumber=nextStatementArray[lineNumber];
    }
    // lineNumber is set to -1 in the end statement
    while(lineNumber!=-1);
}
