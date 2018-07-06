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
namespace Ui {
class network;
}

class network : public QWidget
{
    Q_OBJECT

public:
    explicit network(QWidget *parent = 0);
    ~network();
    QEventLoop *lock;
    QEventLoop *islock[99999];
    QString recdata[99999];
    int allid=0,allrecid=0;
    QTimer *timeouttimer=new QTimer;
    QTimer *maytimeoutnotice=new QTimer;
    QString request(QString data,bool isshow=false);
    //std::string request(std::string data,bool isshow=false);
    void networkrecv();
    void networksend(QString data);
    bool connecttoserver();
    bool needwait=false;
private slots:
    void error();
    void timeoutnotice();
private:
    QTcpSocket *client;
    Ui::network *ui;
};
//void heartpacket(network *net);
void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);
#endif // NETWORK_H
