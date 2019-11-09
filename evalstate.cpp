#include "evalstate.h"

evalstate::evalstate()
{

}

void evalstate::setValue(string str, int value)
{
    if(symbolTable.find(str)==symbolTable.end())
        symbolTable.insert(pair<string,int>(str,value));
    else{
        symbolTable.at(str)=value;
    }
}

int evalstate::getValue(string var)
{
    return symbolTable.at(var);
}

bool evalstate::isDefined(string var)
{
    return symbolTable.find(var)!=symbolTable.end();
}

void evalstate::clear()
{
    this->symbolTable.clear();
}
