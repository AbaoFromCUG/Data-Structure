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
    m_logHelper->setOutWidget(ui->enCodeLog);
    m_frameHelper=new FramelessHelper(this);
    m_frameHelper->activateOn(this);  //激活当前窗体
    m_frameHelper->setTitleHeight(26);  //设置窗体的标题栏高度
    m_frameHelper->setWidgetMovable(true);  //设置窗体可移动
    m_frameHelper->setWidgetResizable(true);  //设置窗体可缩放
    m_frameHelper->setRubberBandOnMove(false);  //设置橡皮筋效果-可移动
    m_frameHelper->setRubberBandOnResize(false);  //设置橡皮筋效果-可缩放


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



void EnCodeDialog::startEnCoder(QString fromName)
{
    QString toFileName= QFileDialog::getSaveFileName(this,
                                                     tr("输入或选择以我规定后缀为后缀的文件!!!"),
                                                     QStandardPaths::standardLocations(QStandardPaths::DesktopLocation)[0], tr("Hoff压缩格式 (*.hoff *.hf *.hof)"));;
    if(toFileName.isEmpty()){
        QMessageBox::warning(this,"2333",tr("你没有输入文件"),QMessageBox::Ok);
        this->close();
        return;
    }
    EnCoder* m_enCoder;
    m_enCoder=new EnCoder();
    m_workThread=new QThread(this);
    m_enCoder->moveToThread(m_workThread);
    connect(m_workThread,&QThread::finished,m_enCoder,&EnCoder::deleteLater);
    connect(m_enCoder,&EnCoder::signal_enCoder,this,&EnCodeDialog::statusChange);
    connect(this,&EnCodeDialog::signal_enCode,m_enCoder,&EnCoder::enCodeFile);
    m_workThread->start();
    emit signal_enCode(fromName,toFileName);


}

void EnCodeDialog::statusChange(int status,double much)
{
    switch (status) {
    case 0:
    {
        m_logHelper->outLog("统计出信息");
        break;
    }
    case 1:
    {
        m_logHelper->outLog("构建树成功");
        break;
    }
    case 2:
    {
        m_logHelper->outLog(QString("正在压缩,压缩了%1%%").arg(much));

        break;
    }
    case 3:
    {
        m_workThread->quit();
        break;
    }
    default:
        break;
    }
    ui->progressBar->setValue(much);
    qDebug()<<much;

}
