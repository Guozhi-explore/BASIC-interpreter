#ifndef EVALSTATE_H
#define EVALSTATE_H

#include<string>
using namespace std;
#include<map>

class evalstate
{
public:
    evalstate();
    void setValue(string str,int value);
    int getValue(string var);
    bool isDefined(string var);
    void clear();

private:
    //store id's value
    map<string,int> symbolTable;

};

#endif // EVALSTATE_H
