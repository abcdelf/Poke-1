#include "helpothers.h"
#include "ui_helpothers.h"

helpothers::helpothers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::helpothers)
{
    ui->setupUi(this);
}

helpothers::~helpothers()
{
    delete ui;
}

void helpothers::on_gohelp_clicked()
{
    if (net->request("helpothersrequestid"+net->FUHAO+ui->id->document()->toPlainText())=="ok")
    {
        ui->gohelp->hide();
        ui->id->setReadOnly(true);
    }
}
