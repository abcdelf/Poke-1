#include "helpchoose.h"
#include "ui_helpchoose.h"

helpchoose::helpchoose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helpchoose)
{
    ui->setupUi(this);
}

helpchoose::~helpchoose()
{
    delete ui;
}

void helpchoose::on_needhelp_clicked()
{
    needhelp *help=new needhelp;
    help->net=net;
    help->init();
    help->show();
    this->hide();
}

void helpchoose::on_helpother_clicked()
{
    helpothers *help=new helpothers;
    help->net=net;
    help->show();
}
