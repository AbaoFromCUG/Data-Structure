#ifndef ENCODEDIALOG_H
#define ENCODEDIALOG_H

#include <QDialog>

namespace Ui {
class EnCodeDialog;
}

class EnCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EnCodeDialog(QWidget *parent = 0);
    ~EnCodeDialog();

private:
    Ui::EnCodeDialog *ui;
};

#endif // ENCODEDIALOG_H
