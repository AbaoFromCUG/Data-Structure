#ifndef ENCODEDIALOG_H
#define ENCODEDIALOG_H

#include <QDialog>
#include<QThread>
#include<QFileDialog>
#include<QDebug>
#include"encoder.h"
#include"lib/logHelper/loghelper.h"
#include"lib/framlessHelper/qwidget/framelesshelper.h"

namespace Ui {
class EnCodeDialog;
}

class EnCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EnCodeDialog(QWidget *parent = 0);
    ~EnCodeDialog();

public slots:

public slots:
    void statusChange(int status, double much);
    void on_toolButton_clicked();
    void startEnCoder(QString fromName);

signals:
    void signal_enCode(QString fromName,QString toName);
private:
    Ui::EnCodeDialog *ui;
    LogHelper* m_logHelper;
    FramelessHelper *m_frameHelper;


    QThread * m_workThread;

};

#endif // ENCODEDIALOG_H
