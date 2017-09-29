#ifndef CACULATOR_H
#define CACULATOR_H
#include"stable.h"
#include"list/stack.h"

/*
 * 为了方便计算，sin，cos,tan ，转换为s，c,t,
 * 单目运算符号有（s、c、t、-)
 * 双目运算符中  加法小于乘除，乘除小于（指数，科学计数法，开方，取余）小于 小数点，  有括号先算括号里的
 * 单目运算符号具有最高的优先级别，s，c，t，-(负号）
 *
 */

class Caculator:public QObject
{
public:
    Caculator(QObject* parent=NULL);
    ~Caculator();
    double startRunning(QString str);       //计算函数

protected:
    bool legitimate(QString expression);//判断两边带#号的表达式是否合法
    bool IsOperator(char c);            //判断一个字符是不是运算符号
    bool kindOpt(char c);
    double calculate(double num1,char opt,double num2); //二元运算符号
    double calculate(double num, char opt);     //一元运算符号
    int getMap(char x, char y);




    int optMap[7][7]={
      /*
       * 1 表示当前运算符大于小于栈顶的运算符号,栈顶符号出栈参与运算,然后在加当前符号push
       * 2 表示当前运算符号大于栈顶的运算符号,直接push
       * 3 表示当前符号是")",需要运算,直到最后将对应的"(" 出栈完毕
       * 4 表示当前符号是"#" 需要将所有的有效运算符号依次出栈参与运算
       * 5 表示遇到非法的符号结对,比如当前是(, 而栈顶是#
       *
                    +-      * /   e^r%    s t c     (       )       #
            +-      1       2       2       2       2       3       4
            * /     1       1       2       2       2       3       4
            e^ r%	1       1       1       2       2       3       4
            s t c	1       1       1       1       2       3       4
            (       2       2       2       2       2       3       5
            )       5       5       5       5       5       5       5
            #       2       2       2       2       2       5       4

        */
        {1,2,2,2,2,3,4},
        {1,1,2,2,2,3,4},
        {1,1,1,2,2,3,4},
        {1,1,1,1,2,3,4},
        {2,2,2,2,2,3,5},
        {5,5,5,5,5,5,5},
        {2,2,2,2,2,5,4}

    };



};


#endif // CACULATOR_H
