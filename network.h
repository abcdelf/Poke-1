#ifndef NETWORK_H
#define NETWORK_H
#include <QEventLoop>
#include <QWidget>
#include <QTcpSocket>
#include <QTimer>
#include <QString>
#include <QMessageBox>
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
    bool connecttoserver();
    QString reply;
    QString request(QString data,bool isshow=true);
    std::string request(std::string data,bool isshow=true);
    void networkrecv();
    void networksend(QString data);
    QTimer *timeouttimer=new QTimer;
private slots:
    void error();
private:
    QTcpSocket *client;
    Ui::network *ui;
};

#endif // NETWORK_H
