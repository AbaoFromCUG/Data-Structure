#ifndef DECODEDIALOG_H
#define DECODEDIALOG_H

#include <QDialog>
#include<QThread>
#include"lib/framlessHelper/qwidget/framelesshelper.h"
#include"lib/logHelper/loghelper.h"
#include"decoder.h"
namespace Ui {
class DeCodeDialog;
}

class DeCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeCodeDialog(QWidget *parent = 0);
    ~DeCodeDialog();

public slots:
    void on_toolButton_clicked();
    void startWorker(QString fromName);
    void statusChange(int status,double much);
signals:
    void signal_DeCode(QString fromName);
private:
    Ui::DeCodeDialog *ui;
    LogHelper* m_logHelper;
    FramelessHelper *m_frameHelper;

    QThread* m_thread;
};

#endif // DECODEDIALOG_H
