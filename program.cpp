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
