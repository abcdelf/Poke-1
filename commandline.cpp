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
        requestnetrecv=new QTimer;
        connect(requestnetrecv,SIGNAL(timeout()),this,SLOT(net_recv_started()));
        connect(this->ui->send,SIGNAL(clicked()),this,SLOT(net_sendtoprocess()));
        requestnetrecv->start(2000);
    }
    else
    {
        process=new QProcess;
        if (isclient) {
            requestnetrecv=new QTimer;
            connect(process,SIGNAL(started()),this,SLOT(net_send_started()));
            connect(process,SIGNAL(readyRead()),this,SLOT(net_send_finished()));
            connect(process,SIGNAL(finished(int)),this,SLOT(netSendReadyready()));
            connect(requestnetrecv,SIGNAL(timeout()),this,SLOT(net_recvtoprocess()));
        }
        else
        {
            process=new QProcess;
            connect(process,SIGNAL(started()),this,SLOT(started()));
            connect(process,SIGNAL(readyRead()),this,SLOT(readyread()));
            connect(process,SIGNAL(finished(int)),this,SLOT(finished()));
            connect(this->ui->send,SIGNAL(clicked()),this,SLOT(sendtoprocess()));
        }
        process->setProgram("cmd");
        process->start(QIODevice::ReadWrite);
    }
}
void CommandLine::closeEvent(QCloseEvent *event){
  event->accept();
  process->close();
  this->deleteLater();
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
void CommandLine::net_send_started(){
    net->request("needhelpstarted");
    requestnetrecv->start(2000);
}
void CommandLine::net_send_finished() {
    net->request("needhelpfinished");
    ui->show->append("Program Exited");
}
void CommandLine::netSendReadyready() {
    QString data=process->readAll();
    ui->show->setText(ui->show->document()->toPlainText()+data);
    ui->show->moveCursor(QTextCursor::End);
    net->request("needhelpsend"+net->FUHAO+data.toLocal8Bit().toBase64());
}
void CommandLine::net_recvtoprocess() {
    QString recv=net->request("needhelprecv");
    if (recv!=net->FUHAO)
    {
        QByteArray send;
        send.fromBase64(recv.toLocal8Bit());
        process->write(send.toStdString().c_str());
    }
}
void CommandLine::net_recv_started() {
    QString recv=net->request("helpothersisstarted");
    if (recv!=net->FUHAO)
    {
        requestnetrecv->stop();
        requestnetrecv->disconnect();
        connect(requestnetrecv,SIGNAL(timeout()),this,SLOT(net_recv_readyread()));
        connect(requestnetrecv,SIGNAL(timeout()),this,SLOT(net_recv_finished()));
        requestnetrecv->start(2000);
    }
}
void CommandLine::net_recv_readyread() {
    QString recv=net->request("helpothersreadyread");
    if (recv!=net->FUHAO)
    {
        QByteArray data;
        data.fromBase64(recv.toLocal8Bit());
        ui->show->setText(ui->show->document()->toPlainText()+QString::fromStdString(data.toStdString()));
        ui->show->moveCursor(QTextCursor::End);
    }
}
void CommandLine::net_sendtoprocess() {
    QString send=ui->command->text();
    net->request("helpotherssend"+net->FUHAO+QString::fromLocal8Bit(send.toLocal8Bit().toBase64().toStdString().c_str()));
    ui->command->clear();
}
void CommandLine::net_recv_finished() {
    QString recv=net->request("helpothersreadyread");
    if (recv!=net->FUHAO)
    {
        ui->show->append("Program Exited");
        ui->command->hide();
        ui->send->hide();
        requestnetrecv->stop();
    }
}
