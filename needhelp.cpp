#include "needhelp.h"
#include "ui_needhelp.h"

needhelp::needhelp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::needhelp)
{
    ui->setupUi(this);
    connect(&this->waitloop,SIGNAL(timeout()),this,SLOT(requestloop()));
}

needhelp::~needhelp()
{
    delete ui;
}

void needhelp::init() {
    id=net->request("needhelpadndgetid");
    this->waitloop.start(2000);
    ui->id->setText(id);
}
void needhelp::requestloop() {
    if (!requested)
    {
        if (net->request("needhelpcheckothershelpyou")=="requested")
        {
            waitloop.stop();
            ui->id->hide();
            requested=true;
            ui->idtips->hide();
            ui->status->setText("Requested");
            waitloop.start(2000);
        }
    }
    else
    {
        QString command=net->request("helpcommandchannelrecv");
        if (command!="wait")
        {
            waitloop.stop();
            ui->status->setText(command);
            waitloop.start(2000);
        }
    }
}
