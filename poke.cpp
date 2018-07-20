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

void Poke::on_gomedia_clicked()
{
    MediaPlayer *mediascreen=new MediaPlayer;
    mediascreen->net=net;
    mediascreen->show();
}

void Poke::on_help_clicked()
{
    helpchoose *help=new helpchoose;
    help->net=net;
    help->show();
}

void Poke::on_commandLine_clicked()
{
    CommandLine *command=new CommandLine(NULL,false,false);
    command->show();
}
