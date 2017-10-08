#include"caculator.h"
Caculator::Caculator(QObject *parent):
    QObject(parent)
{
    setUnDoable(false);
    setReDoable(false);
}

Caculator::~Caculator()
{

}

QString Caculator::getShowText()
{
    QString allStr;
    Stack<QString> midStack=unStack;
    Stack<QString> midStack2;
    while (!midStack.empty()) {
        midStack2.push(midStack.pop());
    }
    while (!midStack2.empty()) {
        //+-x/ . sin x²÷ UnDo Clear ReDo √
        QString str=midStack2.pop();
        if (str=="x²") {
            allStr.append("²");
        }else if (str=="÷") {
            allStr.append("/");
        }else {
            allStr.append(str);
        }

    }

    return allStr;

}

bool Caculator::unDoable()
{
    return m_unDoable;
}

void Caculator::setUnDoable(bool arg)
{
    if(arg==m_unDoable)
        return;
    m_unDoable=arg;
    emit unDoableChanged(arg);
}

bool Caculator::reDoable()
{
    return m_reDoable;
}

void Caculator::setReDoable(bool arg)
{
    if(arg==m_reDoable)
        return;
    m_reDoable=arg;
    emit reDoableChanged(arg);
}

void Caculator::addDo(QString str)
{
    if(str=="=")
    {
        connect(this,&Caculator::runOver,[=](int status,QString str){
            unStack.clear();
            reStack.clear();
            setUnDoable(true);
            setReDoable(false);
            if(status==0){
                foreach (auto c, str) {
                    unStack.push(QString(c));
                }
            }
        });
        startRunning();

        return;
    }else if (str=="UnDo") {
        //
        if(unDoable()){
            reStack.push(unStack.pop());
            setReDoable(true);
        }else{
            qDebug()<<"Can't ReDo";
            //error;
        }
        if(unStack.empty()){
            setUnDoable(false);
        }
    }else if (str=="ReDo"){
        if(reDoable()){
            unStack.push(reStack.pop());
            setUnDoable(true);
        }else {
            //error
        }
        if(reStack.empty()){
            setReDoable(false);
        }
    }else if (str=="Clear") {
        setUnDoable(false);
        setReDoable(false);
        unStack.clear();
        reStack.clear();
    }else {
        unStack.push(str);
        if(!unDoable()){
            setUnDoable(true);
        }
    }

}

void Caculator::startRunning()
{
    QString str=getRunText();
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

                    emit runOver( 1,"非法,一个数据含有两个小数点") ;
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
                        emit (1,"负数表示非法");
                        return;
                    }else {
                        if(cache.count('.')<=1){
                            numStack.push(cache.toDouble());
                            c=str[k++].toLatin1();
                        }else {
                            emit runOver(1,"非法,一个数据含有两个小数点") ;
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
                        emit runOver(1,"符号不匹配,非法");
                        return;
                    }else {
                        emit runOver(0,QString::number(numStack.pop()));
                        return ;
                    }
                    break;
                }

                case 5:{
                    emit runOver(1,"符号不匹配,非法");
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
                 */
                emit runOver(1,"含有非运算符号的符号");
                return;
            }
            c=str[k++].toLatin1();

        }





    }
    catch(QString str){
        emit runOver(1,str);
    }catch(...){
        emit runOver(1,"遇到不知名错误");
    }


}

QString Caculator::getRunText()
{
    QString allStr;
    Stack<QString> midStack=unStack;
    Stack<QString> midStack2;
    while (!midStack.empty()) {
        midStack2.push(midStack.pop());
    }
    while (!midStack2.empty()) {
        //+-x/ . sin x²÷ UnDo Clear ReDo √
        QString str=midStack2.pop();
        if(str=="sin"||str=="cos"||str=="tan"){
            allStr.append(str[0]);
        }else if(str=="x"){
            allStr.append("*");
        }else if (str=="x²") {
            allStr.append("^2");
        }else if (str=="÷") {
            allStr.append("/");
        }else if (str=="√") {
            allStr.append("r");
        }else {
            allStr.append(str);
        }

    }


    return allStr;
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
            emit runOver(1, "被除数不能为零");
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
