#ifndef NETWORK_H
#define NETWORK_H
#include <QEventLoop>
#include <QWidget>
#include <QTcpSocket>
#include <QTimer>
#include <vector>
#include <QString>
#include <QMessageBox>
#include <thread>
#include <QApplication>
#include <QCloseEvent>
namespace Ui {
class network;
}

class network : public QWidget
{
    Q_OBJECT

public:
    explicit network(QWidget *parent = 0);
    ~network();
    bool isok=true;
    QString FUHAO;
    QEventLoop *lock;
    QEventLoop *islock[99999];
    QString recdata[99999];
    QString username;
    QString token;
    bool  islogin=false;
    int allid=0,allrecid=0;
    QTimer *timeouttimer=new QTimer;
    QTimer *maytimeoutnotice=new QTimer;
    QString request(QString data,bool isshow=false,bool directrequest=false);
    //std::string request(std::string data,bool isshow=false);
    void networkrecv();
    void networksend(QString data);
    bool connecttoserver();
    void reconnect();
    bool needwait=false;

    QApplication *main;
    bool exit=false;
private slots:
    void error();
    void timeoutnotice();
private:
    QTcpSocket *client;
    Ui::network *ui;
    void closeEvent(QCloseEvent * event);
signals:
    void terminate_signal();
};
void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);
struct network_list
{
    int num;
    QString recdata;
    QEventLoop islock;
    struct network_list *next=NULL;
};



#endif // NETWORK_H

