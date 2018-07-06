#include "loginscreen.h"
#include "ui_loginscreen.h"

loginscreen::loginscreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginscreen)
{
    ui->setupUi(this);
}

loginscreen::~loginscreen()
{
    wait_login->quit();
    delete ui;
}

void loginscreen::on_go_clicked()
{
    if (islogin)
    {
        if (net->request("login "+ui->username->text()+" "+ui->password->text(),true)=="success")
        {          
            islogined=true;
            ui->emsg->clear();
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
        if (net->request("reg "+ui->username->text()+" "+ui->password->text(),true)=="success")
        {
            islogined=true;
            ui->emsg->clear();
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
