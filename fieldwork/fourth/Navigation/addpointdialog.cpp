#include "addpointdialog.h"
#include "ui_addpointdialog.h"
#include"lib/framlessHelper/qwidget/framelesshelper.h"
AddPointDialog::AddPointDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointDialog)
{
    ui->setupUi(this);
    FramelessHelper* helper=new FramelessHelper(this);
    helper->activateOn(this);  //激活当前窗体
    helper->setTitleHeight(60);  //设置窗体的标题栏高度
    helper->setWidgetMovable(true);  //设置窗体可移动
    helper->setWidgetResizable(true);  //设置窗体可缩放
    helper->setRubberBandOnMove(false);  //设置橡皮筋效果-可移动
    helper->setRubberBandOnResize(false);  //设置橡皮筋效果-可缩放

}

AddPointDialog::~AddPointDialog()
{
    delete ui;
}

int AddPointDialog::addPoint(QPointF p)
{
    AddPointDialog add;
    add.m_locaPos=p;
    add.exec();

}

//添加的按钮
void AddPointDialog::on_pushButton_2_clicked()
{
    if(ui->comboBox->currentIndex()==0){
        QMessageBox::warning(this,"非法","对不起，请选着关键点的类型");
        return;
    }
    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::warning(this,"非法","对不起，请输入这个地点的名称");
        return;
    }
    if(ui->textEdit->toPlainText().isEmpty()){
        QMessageBox::warning(this,"非法","对不起，请输入这个地点的描述");
        return;
    }
    if(ui->checkBox->isChecked()){

        if(m_imgFile.isEmpty()){
            QMessageBox::warning(this,"非法","对不起，你还没有选择这个地点的预览图片");
            return;
        }
    }else{
        MapProfileReader* reader=MapProfileReader::getInstance();
        ViewPoint p;
        p.name=ui->lineEdit->text();;
        p.index=reader->getPointCount();
        p.x=this->m_locaPos.x();
        p.y=this->m_locaPos.y();
        p.type=ui->comboBox->currentIndex();;
        p.imgSrc=this->m_imgFile;
        p.desc=ui->textEdit->toPlainText();;
        reader->addNewViewPoint(p);
        this->close();
    }

}

void AddPointDialog::on_pushButton_3_clicked()
{
    this->close();
}

void AddPointDialog::on_file_clicked()
{
//    QFileDialog::getSaveFileName(this,)
}
