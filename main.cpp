#include <QApplication>
#include <QObject>
#include <iostream>
#include <string>
#include "loginscreen.h"
#include "poke.h"
#include "network.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    network net;
    net.show();
    if (!net.connecttoserver())
    {    
        return -1;
    }
    loginscreen login;
    QObject::connect(&net,SIGNAL(terminate_signal()),&login,SLOT(terminate_loginscreen()));
    QEventLoop wait_login;
    login.net=&net;
    login.wait_login=&wait_login;
    login.show();
    wait_login.exec();
    if (!net.exit)
    {
        if (!login.islogined)
        {
            return 0;
        }
        if (!net.exit)
        {
            Poke *w=new Poke;
            w->net=&net;
            w->show();
            a.exec();
        }
        else
        {
            return 0;
        }
        return 0;
    }
    else
    {
        return 0;
    }
}
