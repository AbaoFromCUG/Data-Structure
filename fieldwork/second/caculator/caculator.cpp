#include"caculator.h"
Caculator::Caculator(QObject *parent):
    QObject(parent)
{


}

Caculator::~Caculator()
{

}

double Caculator::startRunning(QString str)
{
    try{
        Stack<char> optStack;
        Stack<double> numStack;
        str.append('#');
        optStack.push('#');
        char c=str[0].toLatin1();
        int k=1;

        while (c) {
            if(c<='9'&&c>='0'||c=='.'){
                QString cache;
                while(c<='9'&&c>='0'||c=='.'){
                    cache.append(c);
                    c=str[k++].toLatin1();
                }
                if(cache.count('.')<=1){
                    numStack.push(cache.toDouble());
                }else {
                    throw QString("非法,一个数据含有两个小数点") ;
                }
                continue;
            }

            else if (IsOperator(c)) {
                if(c=='('&&str[k]=='-'){
                    /*
                     * 如果遇到(, 且它后面一个符号是负号时,
                     * 则直接运行到负数完,
                     * 且仅仅支持(-12)类型的符号
                     */
                    k++;
                    c=str[k].toLatin1();
                    QString cache("-");
                    while(c<='9'&&c>='0'||c=='.'){
                        cache.append(c);
                        c=str[++k].toLatin1();
                    }
                    if(c!=')'){
                        //如果将负号后面一个数字扫描完毕,但是后面的不是)的话
                        //非法
                        throw QString("负数表示非法");
                    }else {
                        if(cache.count('.')<=1){
                            numStack.push(cache.toDouble());
                            c=str[k++].toLatin1();
                        }else {
                            throw QString("非法,一个数据含有两个小数点") ;
                        }
                    }
                    continue;

                }


                qDebug()<<c<<"   "<<getMap(c,optStack.top());
                switch (getMap(c,optStack.top())) {
                  /*
                   * 1 表示当前运算符大于小于栈顶的运算符号,栈顶符号出栈参与运算,然后在加当前符号push
                   * 2 表示当前运算符号大于栈顶的运算符号,直接push
                   * 3 表示当前符号是")",需要运算,直到最后将对应的"(" 出栈完毕
                   * 4 表示当前符号是"#" 需要将所有的有效运算符号依次出栈参与运算
                   * 5 表示遇到非法的符号结对,比如当前是(, 而栈顶是#
                   */
                case 1:
                {
                    if(kindOpt(optStack.top())){
                        double num1=numStack.pop();
                        double num2=numStack.pop();
                        char o=optStack.pop();
                        numStack.push(this->calculate(num2,o,num1));

                    }else {
                        numStack.push(this->calculate(numStack.pop(),optStack.pop()));
                    }
                    optStack.push(c);
                    break;
                }
                case 2:{
                    optStack.push(c);
                    break;
                }
                case 3:
                {
                    while (optStack.top()!='(') {
                        if(kindOpt(optStack.top())){
                            double num1=numStack.pop();
                            double num2=numStack.pop();
                            char o=optStack.pop();
                            numStack.push(this->calculate(num2,o,num1));

                        }else {
                            numStack.push(this->calculate(numStack.pop(),optStack.pop()));
                        }

                    }
                    optStack.pop();
                    break;
                }
                case 4:
                {
                    while (optStack.top()!='#') {
                        if(kindOpt(optStack.top())){
                            double num1=numStack.pop();
                            double num2=numStack.pop();
                            char o=optStack.pop();
                            numStack.push(this->calculate(num2,o,num1));

                        }else {
                            numStack.push(this->calculate(numStack.pop(),optStack.pop()));
                        }

                    }
                    optStack.pop();
                    if(numStack.getLength()!=1){
                        throw QString("符号不匹配,非法");
                    }else {
                        return numStack.pop();
                    }
                    break;
                }
                default:
                    break;
                }
            }

            else {
                /*
                 * 既不是数字也不是运算符号,所以输入非法,
                 * 先抛个异常
                 */\
                 throw QString("error ,含有非运算符号的符号");
            }
            c=str[k++].toLatin1();

        }





    }
    catch(QString str){
        throw str;
    }catch(...){
        qDebug()<<"遇到不知名错误";
    }
    return 0;


}


bool Caculator::legitimate(QString expression)
{

}

bool Caculator::IsOperator(char c)
{
    switch (c) {
    case '+':
    case '-':
    case '*':
    case '%':
    case 'r':
    case '^':
    case '/':
    case 'e':
    case 's':
    case 'c':
    case 't':
    case '#':
    case '(':
    case ')':
        return true;
        break;


    default:
        return false;

        break;
    }

}

bool Caculator::kindOpt(char c)
{
    switch (c) {
    case '+':
    case '-':
    case '*':
    case '/':
    case 'r':
    case '^':
    case '%':
    case 'e':
        return true;
    case 's':
    case 'c':
    case 't':
        return false;
    default:
        break;
    }

}
double Caculator::calculate(double num1, char opt, double num2)
{
    switch (opt) {
    case '+':
        return num1+num2;
        break;
    case '-':
        return num1-num2;
        break;
    case '*':
        return num1*num2;
        break;
    case '.':
        return QString("%1.%2").arg((int)num1).arg((int)num2).toDouble();
    case '/':
        if(abs(num2)<0.00000001){
            throw QString("被除数不能为零");
        }
        return num1/num2;
        break;
    case '^':
        return pow(num1,num2);
        break;
    case 'e':
        return  num1*pow(10,num2);
        break;
    case 'r':
        return pow(num2,1.0/num1);
        break;
    case '%':
        return ((int)num1)%((int)num2);
        break;
    default:
        break;
    }

}

double Caculator::calculate(double num, char opt)
{
    switch (opt) {
    case 's':
        return sin(num);
        break;
    case 'c':
        return cos(num);
        break;
    case 't':
        return tan(num);
        break;
    default:
        break;
    }

}

int Caculator::getMap(char x, char y)
{
    //     +-      * /   e^r%    s t c     (       )       #
    int i=6,j=5;        //默认是非法了的,也就是说5
    switch (x) {
    case '+':
    case '-':i=0;break;

    case '*':
    case '/':i=1;break;

    case 'e':
    case '^':
    case 'r':
    case '%':
        i=2;break;

    case 's':
    case 't':
    case 'c':
        i=3;break;

    case '(':i=4;break;
    case ')':i=5;break;
    case '#':i=6;break;
    default:
        break;
    }
    switch (y) {
    case '+':
    case '-':j=0;break;

    case '*':
    case '/':j=1;break;

    case 'e':
    case '^':
    case 'r':
    case '%':
        j=2;break;

    case 's':
    case 't':
    case 'c':
        j=3;break;

    case '(':j=4;break;
    case ')':j=5;break;
    case '#':j=6;break;
    default:
        break;
    }

    return this->optMap[j][i];

}
