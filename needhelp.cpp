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
    this->waitloop.start(1000);
    ui->id->setText(id);
}
void needhelp::requestloop() {
    if (net->request("needhelpcheckothershelpyou")=="requested")
    {
        waitloop.stop();
        ui->id->hide();
        ui->idtips->hide();
        ui->status->setText("Requested");
    }
}
