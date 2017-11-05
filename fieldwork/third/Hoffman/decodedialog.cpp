#include "decodedialog.h"
#include "ui_decodedialog.h"

DeCodeDialog::DeCodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeCodeDialog)
{
    ui->setupUi(this);
}

DeCodeDialog::~DeCodeDialog()
{
    delete ui;
}

void DeCodeDialog::on_toolButton_clicked()
{
    if(ui->enCodeLog->isHidden()){
        ui->enCodeLog->show();
    }else {
        ui->enCodeLog->hide();
    }
}

void DeCodeDialog::startWorker(QString fromName)
{
//    if(toFileName.isEmpty()){
//        QMessageBox::warning(this,"2333",tr("你没有输入文件"),QMessageBox::Ok);
//        this->close();
//        return;
//    }

}
