#ifndef ADDPOINTDIALOG_H
#define ADDPOINTDIALOG_H

#include <QDialog>
#include<QPointF>
#include<QMessageBox>
#include"mapprofilereader.h"
#include<QFileDialog>
namespace Ui {
class AddPointDialog;
}

class AddPointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPointDialog(QWidget *parent = 0);
    ~AddPointDialog();
    int static addPoint(QPointF p);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_file_clicked();

private:
    Ui::AddPointDialog *ui;
    QString m_imgFile;
    QPointF m_locaPos;
};

#endif // ADDPOINTDIALOG_H
