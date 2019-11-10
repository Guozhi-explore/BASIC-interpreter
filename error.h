#ifndef ERROR_H
#define ERROR_H

#include<exception>
#include<string>
using namespace std;

class ErrorException:public exception
{
public:
    ErrorException(string errorMessage);
    ~ErrorException() throw();
    string getMessage();

private:
    string errorMessage;
};
extern
void error(string errorMessage);
void printToConsole(string errorMessage);
#endif // ERROR_H
