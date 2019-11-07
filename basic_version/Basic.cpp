#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main()
{
    string str;
    while(true)
    {
        try{
            getline(std::cin,str);
        }
        catch(ifstream::failure e)
        {
            cerr<<"exception read user input\n";
        }
        handle(input_line);
    }
    return 0;
}

void handle(string input_line)
{

}