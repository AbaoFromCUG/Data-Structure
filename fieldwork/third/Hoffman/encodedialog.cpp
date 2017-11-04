#include "encodedialog.h"
#include "ui_encodedialog.h"

EnCodeDialog::EnCodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnCodeDialog)
{
    ui->setupUi(this);
}

EnCodeDialog::~EnCodeDialog()
{
    delete ui;
}
