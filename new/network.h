#ifndef NETWORK_H
#define NETWORK_H
#include <QTcpSocket>
#include <QCloseEvent>
#include <QMessageBox>
#include <QEventLoop>
#include <QWidget>
#include <QMap>
#define SERVERIP "localhost"
#define SERVERPORT 8864
namespace Ui {
class network;
}

class network : public QWidget
{
    Q_OBJECT

public:
    explicit network(QWidget *parent = 0);
    ~network();
    static QString protocol_encode(QString command,QString parameter);
    static QString protocol_decode(QString data);
    void connect();
    QString request(QString data);
private slots:
    void readyread();
private:
    QTcpSocket *socket;
    QMap<int,QString> mapbackvalue;
    QMap<int,QEventLoop> mapwaitreply;
    QMap<int,bool> isfinished;
    int sid=0,rid=0;
    Ui::network *ui;
    void closeEvent(QCloseEvent *event);


};

#endif // NETWORK_H
