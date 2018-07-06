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

void Poke::on_submit_clicked()
{
    ui->textBrowser->setText(net->request(ui->lineEdit->text()));
}

void Poke::on_gochat_clicked()
{
    ChatScreen *chat=new ChatScreen;
    chat->net=net;
    chat->joinchat();
    chat->show();
}
