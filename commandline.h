#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QWidget>
#include <QProcess>
namespace Ui {
class CommandLine;
}

class CommandLine : public QWidget
{
    Q_OBJECT

public:
    explicit CommandLine(QWidget *parent = 0,bool isremote=false,bool isclient=false);
    ~CommandLine();

private slots:
    void started();
    void finished();
    void readyread();
    void sendtoprocess();
//    void net_recv_started();
//    void net_recv_finished();
//    void net_recv_readyread();
//    void net_send_started();
//    void net_send_finished();
//    void net_send_readyready();
private:
    bool isremote;
    Ui::CommandLine *ui;
    QProcess *process;
};

#endif // COMMANDLINE_H
