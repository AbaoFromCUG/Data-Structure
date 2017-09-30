#include"list/stack.h"
#include"stable.h"
#include<iostream>
#include"stack"
#include"caculator.h"


int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    //return a.exec();
    Caculator cc;
    while (true) {
        std::string str;
        qDebug()<<"请输入你要计算的表达式";
        std::cin>>str;
        try{
            qDebug()<<cc.startRunning(QString(str.c_str()));
        }catch(char* cc){


            //qDebug()<<cc;
        }catch(QString str){
            qDebug()<<str;
        }


    }
    return 0;
}
