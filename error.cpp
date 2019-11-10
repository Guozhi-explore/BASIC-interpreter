#include "error.h"

ErrorException::ErrorException(string errorMessage)
{
    this->errorMessage=errorMessage;
}

ErrorException::~ErrorException() throw()
{

}
string ErrorException::getMessage()
{
    return this->errorMessage;
}

void error(string errorMessage)
{
    throw ErrorException(errorMessage);
}

void printToConsole(string errorMessage)
{
    throw ErrorException(errorMessage);
}
