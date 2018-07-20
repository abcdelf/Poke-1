#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QWidget>
#include <QProcess>
#include <QArrayData>
#include <QCloseEvent>
#include <QTimer>
#include "network.h"
namespace Ui {
class CommandLine;
}

class CommandLine : public QWidget
{
    Q_OBJECT

public:
    explicit CommandLine(QWidget *parent = 0,bool isremote=false,bool isclient=false);
    ~CommandLine();
    network *net;
    void init();
private slots:
    void started();
    void finished();
    void readyread();
    void sendtoprocess();
    void net_send_started();
    void net_send_finished();
    void netSendReadyready();
    void net_recvtoprocess();
    void net_recv_started();
    void net_recv_finished();
    void net_recv_readyread();
    void net_sendtoprocess();
private:
    int allprintfed=0;
    QTimer *requestnetrecv;
    bool isremote;
    Ui::CommandLine *ui;
    QProcess *process;
    void closeEvent(QCloseEvent *event);
};

#endif // COMMANDLINE_H
