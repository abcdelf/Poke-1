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
        this->hide();
        CommandLine *command=new CommandLine(NULL,true);
        command->net=net;
        command->show();
        this->deleteLater();
    }
}

