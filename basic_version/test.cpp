#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main()
{
    struct test{
        int a;
        string b;
    };
    vector<test> array;
    test t;
    t.a=1;
    t.b="1345";
    array.push_back(t);
    printf("%u\n",array.size());
    return 0;
}