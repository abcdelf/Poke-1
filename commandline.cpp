#include "commandline.h"
#include "ui_commandline.h"
#include <iostream>
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
        requestnetrecv=new QTimer(this);
        connect(requestnetrecv,SIGNAL(timeout()),this,SLOT(net_recv_started()));
        connect(this->ui->send,SIGNAL(clicked()),this,SLOT(net_sendtoprocess()));
        requestnetrecv->start(2000);
    }
    else
    {
        process=new QProcess(this);
        if (isclient) {
            requestnetrecv=new QTimer;
            connect(process,SIGNAL(started()),this,SLOT(net_send_started()));
            connect(process,SIGNAL(readyRead()),this,SLOT(netSendReadyready()));
            connect(process,SIGNAL(finished(int)),this,SLOT(net_send_finished()));
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

    }
}
void CommandLine::closeEvent(QCloseEvent *event){
  if (!isremote)
  {
    process->close();
  }
  event->accept();
  this->deleteLater();
}
CommandLine::~CommandLine()
{
    delete ui;
}
void CommandLine::init() {
    process->setProgram("cmd");
    process->start(QIODevice::ReadWrite);
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
    requestnetrecv->stop();
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
    requestnetrecv->stop();
    QString recdata=net->request("needhelprecv"+net->FUHAO+QString::number(allprintfed));
    if (recdata==net->FUHAO)
    {
        return;
    }
    std::vector<std::string> datamap;
    SplitString(recdata.toStdString(),datamap,"$");
    if (datamap.size()>0)
    {
        int allnow=atoi(datamap[0].c_str());
        while(allprintfed<allnow)
        {
            process->write(QByteArray::fromBase64(QString::fromStdString(datamap[allnow-allprintfed]).toLocal8Bit()));
            process->write("\r\n");
            allprintfed++;
        }
    }
    requestnetrecv->start(2000);
}
void CommandLine::net_recv_started() {
    QString recv=net->request("helpothersisstarted");
    if (recv!=net->FUHAO)
    {
        requestnetrecv->stop();
        requestnetrecv->disconnect();
        connect(requestnetrecv,SIGNAL(timeout()),this,SLOT(net_recv_readyread()));
        connect(requestnetrecv,SIGNAL(timeout()),this,SLOT(net_recv_finished()));
        ui->command->show();
        ui->send->show();
        requestnetrecv->start(2000);
    }
}
void CommandLine::net_recv_readyread() {
    requestnetrecv->stop();
    QString recdata=net->request("helpothersrecv"+net->FUHAO+QString::number(allprintfed)),addtmp;
    if (recdata==net->FUHAO)
    {
        return;
    }
    std::vector<std::string> datamap;
    SplitString(recdata.toStdString(),datamap,"$");
    if (datamap.size()>0)
    {
        int allnow=atoi(datamap[0].c_str());
        while(allprintfed<allnow)
        {
            addtmp=addtmp+QString::fromStdString(QByteArray::fromBase64(QString::fromStdString(datamap[allnow-allprintfed]).toLocal8Bit()).toStdString());
            allprintfed++;
        }
        if (addtmp!="")
        {
            ui->show->setText(ui->show->document()->toPlainText()+QString::fromStdString(addtmp.toStdString()));
            ui->show->moveCursor(QTextCursor::End);
        }
    }
    requestnetrecv->start(2000);

}
void CommandLine::net_sendtoprocess() {
    QString send=ui->command->text();
    net->request("helpotherssend"+net->FUHAO+QString::fromLocal8Bit(send.toLocal8Bit().toBase64().toStdString().c_str()));
    ui->command->clear();
}
void CommandLine::net_recv_finished() {
    QString recv=net->request("helpothersisfinished");
    if (recv!=net->FUHAO)
    {
        ui->show->append("Program Exited");
        ui->command->hide();
        ui->send->hide();
        requestnetrecv->stop();
    }
}
