#include "loginscreen.h"
#include "ui_loginscreen.h"
#include <iostream>
loginscreen::loginscreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginscreen)
{
    ui->setupUi(this);
}

loginscreen::~loginscreen()
{
    //wait_login->quit();
    delete ui;
}

void loginscreen::on_go_clicked()
{
    if (islogin)
    {
        QString tmp=net->request("login"+net->FUHAO+ui->username->text()+net->FUHAO+ui->password->text());
        if (tmp!="Error")
        {          
            islogined=true;
            ui->emsg->clear();
            net->username=ui->username->text();
            net->token=tmp;
            net->islogin=true;

            this->accept();            
            wait_login->quit();
        }
        else
        {
            ui->username->clear();
            ui->password->clear();
            ui->emsg->setText("Username or Password Wrong");
        }
    }
    else
    {
        QString tmp=net->request("reg"+net->FUHAO+ui->username->text()+net->FUHAO+ui->password->text());
        if (tmp!="Error")
        {
            islogined=true;
            ui->emsg->clear();
            net->username=ui->username->text();
            net->token=tmp;
            net->islogin=true;
            this->accept();
            wait_login->quit();
        }
        else
        {
            ui->username->clear();
            ui->password->clear();
            ui->emsg->setText("Username Repeat");
        }
    }
}

void loginscreen::on_pushButton_clicked()
{
    if (islogin)
    {
        ui->t->setText("Reg");
        islogin=false;
        ui->pushButton->setText("login?");
    }
    else
    {
        ui->t->setText("Login");
        islogin=true;
        ui->pushButton->setText("Register?");
    }
}

void loginscreen::closeEvent(QCloseEvent *event)
{
    event->accept();
    wait_login->quit();
}
void loginscreen::terminate_loginscreen(){
    this->hide();
    //this->deleteLater();
    wait_login->quit();
}
