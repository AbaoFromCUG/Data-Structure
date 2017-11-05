#ifndef DECODEDIALOG_H
#define DECODEDIALOG_H

#include <QDialog>
#include<QThread>
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

private slots:
    void on_toolButton_clicked();
    void startWorker(QString fromName);
private:
    Ui::DeCodeDialog *ui;
    DeCoder* m_deCoder;
    QThread* m_thread;
};

#endif // DECODEDIALOG_H
