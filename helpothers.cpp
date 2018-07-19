#include "helpothers.h"
#include "ui_helpothers.h"

helpothers::helpothers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::helpothers)
{
    ui->setupUi(this);
    ui->command->hide();
    ui->send->hide();
    ui->reply->hide();
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
        ui->command->show();
        ui->send->show();
        ui->reply->show();
    }
}

void helpothers::on_send_clicked()
{
    ui->send->hide();
    ui->command->setReadOnly(true);
    net->request("helpotherscommandchannelsend"+net->FUHAO+ui->command->text());
}
