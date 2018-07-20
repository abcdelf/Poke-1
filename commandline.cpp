#include "commandline.h"
#include "ui_commandline.h"

CommandLine::CommandLine(QWidget *parent,bool isremote,bool isclient) :
    QWidget(parent),
    ui(new Ui::CommandLine)
{
    /*
     * isremote true:
     * helpothers
     * isremote false:
     * isclient true:
     * needhelp
     * else
     * commandline
     */
    ui->setupUi(this);
    ui->show->setReadOnly(true);
    ui->command->hide();
    ui->send->hide();
    this->isremote=isremote;
    if (isremote) {

    }
    else{
        if (isclient) {

        }
        else
        {
            process=new QProcess;
            connect(process,SIGNAL(started()),this,SLOT(started()));
            connect(process,SIGNAL(readyRead()),this,SLOT(readyread()));
            connect(process,SIGNAL(finished(int)),this,SLOT(finished()));
            connect(this->ui->send,SIGNAL(clicked()),this,SLOT(sendtoprocess()));
            process->setProgram("cmd");
            process->start(QIODevice::ReadWrite);
        }
    }
}

CommandLine::~CommandLine()
{
    delete ui;
}
void CommandLine::started(){
    ui->command->setReadOnly(false);
    ui->command->show();
    ui->send->show();
}
void CommandLine::finished() {
    ui->show->setReadOnly(true);
    ui->command->setReadOnly(true);
    ui->send->hide();
    ui->show->append("Program Exited");
}
void CommandLine::readyread() {
    ui->show->setText(ui->show->document()->toPlainText()+process->readAll());
    ui->show->moveCursor(QTextCursor::End);
}
void CommandLine::sendtoprocess() {
    QString send=ui->command->text()+"\r\n";
    process->write(send.toLocal8Bit());
    ui->command->clear();
}
