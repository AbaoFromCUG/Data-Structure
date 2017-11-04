
#include <QApplication>
#include<QTextCodec>
#include"mainwindow.h"
#include"encoder.h"
#include"decoder.h"
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF8"));


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
