#ifndef OUTPUT_H
#define OUTPUT_H
#include<string>
using namespace std;
#include <QObject>
#include<QWidget>
class inputAndOutput:public QWidget
{
    Q_OBJECT
public:
    inputAndOutput();

signals:
    void  sendOutput(string str);
    void  receiveInput(string value);
};

#endif // OUTPUT_H
