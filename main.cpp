#include "poke.h"
#include "network.h"
#include <QApplication>
#include <iostream>
#include <string>
#include "loginscreen.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    network net;
    net.show();
    if (!net.connecttoserver())
    {
        a.exec();
        return -1;
    }
    loginscreen login;
    QEventLoop wait_login;
    login.net=&net;
    login.wait_login=&wait_login;
    login.show();
    wait_login.exec();
    if (!login.islogined)
    {
        return 0;
    }
    Poke w;
    w.net=&net;
    w.show();
    return a.exec();
}
