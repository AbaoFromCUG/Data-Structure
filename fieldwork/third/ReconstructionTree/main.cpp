#include <QCoreApplication>
#include<struct/CharTree.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CharTree s;
    /*
     * 前序列  ABCDEGF
     *中序列  CBEGDFA
     */
    s.reconstruction("ABCDEGF","CBEGDFA");
    return a.exec();
}
