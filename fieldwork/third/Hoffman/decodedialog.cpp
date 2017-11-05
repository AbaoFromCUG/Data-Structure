#include "decodedialog.h"
#include "ui_decodedialog.h"

DeCodeDialog::DeCodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeCodeDialog)
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
    m_thread=new QThread(this);
    DeCoder* worker=new DeCoder();
    worker->moveToThread(m_thread);
    connect(m_thread,&QThread::finished,worker,&DeCoder::deleteLater);
    connect(worker,&DeCoder::signal_deCoder,this,&DeCodeDialog::statusChange);
    connect(this,&DeCodeDialog::signal_DeCode,worker,&DeCoder::deCodeFile);
    m_thread->start();
    emit signal_DeCode(fromName);

}

void DeCodeDialog::statusChange(int status, double much)
{
    switch (status) {
    case 0:
    {
        m_logHelper->outLog("还原出文件的基本信息");
        break;
    }
    case 1:
    {
        m_logHelper->outLog("构建树成功");
        break;
    }
    case 2:
    {
        m_logHelper->outLog(QString("正在解压,解压了%1%%").arg(much));

        break;
    }
    case 3:
    {
        m_thread->quit();
        break;
    }
    default:
        break;
    }
    ui->progressBar->setValue(much);
    qDebug()<<much;

}
