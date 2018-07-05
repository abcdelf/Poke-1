#include "poke.h"
#include "ui_poke.h"

Poke::Poke(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Poke)
{
    ui->setupUi(this);
}

Poke::~Poke()
{
    delete ui;
}
