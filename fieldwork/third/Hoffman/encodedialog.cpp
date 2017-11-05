#include "encodedialog.h"
#include "ui_encodedialog.h"
#include<QMessageBox>
#include<QStandardPaths>
EnCodeDialog::EnCodeDialog(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::EnCodeDialog)
{
    ui->setupUi(this);
    m_logHelper=new LogHelper(this);
    m_frameHelper=new FramelessHelper(this);


}

EnCodeDialog::~EnCodeDialog()
{
    delete ui;
}

void EnCodeDialog::on_toolButton_clicked()
{
    if(ui->enCodeLog->isHidden()){
        ui->enCodeLog->show();
    }else {
        ui->enCodeLog->hide();
    }
}

void EnCodeDialog::on_cancle_clicked()
{

}

void EnCodeDialog::startEnCoder(QString fromName)
{
    QString toFileName= QFileDialog::getOpenFileName(this,
                                                     tr("输入或选择以我规定后缀为后缀的文件!!!"),
                                                     QStandardPaths::standardLocations(QStandardPaths::DesktopLocation)[0], tr("Hoff压缩格式 (*.hoff *.hf *.hof)"));;
    if(toFileName.isEmpty()){
        QMessageBox::warning(this,"2333",tr("你没有输入文件"),QMessageBox::Ok);
        this->close();
        return;
    }
    m_enCoder=new EnCoder();
    m_workThread=new QThread(this);
    connect(m_workThread,&QThread::finished,m_enCoder,&EnCoder::deleteLater);
    connect(m_enCoder,&EnCoder::signal_enCoder,this,&EnCodeDialog::statusChange);
    connect(this,&EnCodeDialog::signal_enCode,m_enCoder,&EnCoder::enCodeFile);
    m_workThread->start();
    emit signal_enCode(fromName,toFileName);

}

void EnCodeDialog::statusChange(int status,int much)
{
    ui->progressBar->setValue(much);

}
