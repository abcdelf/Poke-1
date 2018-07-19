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
