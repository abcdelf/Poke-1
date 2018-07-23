#include "network.h"
#include "ui_network.h"

network::network(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::network)
{
        ui->setupUi(this);
#ifdef WIN32
       setWindowFlags(windowFlags() &~ Qt::WindowCloseButtonHint);
#endif     
       socket=new QTcpSocket;
}

network::~network()
{
    delete ui;
}
void network::connect() {
    ui->status->setText("connecting...");
    socket->connectToHost(SERVERIP,SERVERPORT);
    if (socket->waitForConnected())
    {
        ui->status->setText("connected");
        QObject::connect(socket, &QTcpSocket::readyRead, this, &network::readyread);
        QObject::connect(socket, &QTcpSocket::disconnected, this, &network::connect,Qt::QueuedConnection);
    }
    else
    {
        ui->status->setText("not connected");
    }

}
void network::closeEvent(QCloseEvent *event)
{
    event->ignore();
    QMessageBox::information(this,"Network","The Network Manger will close \nWhen you close the main window",QMessageBox::Yes);
}
QString network::protocol_encode(QString command,QString parameter) {
    QByteArray c=command.toLocal8Bit();
    QByteArray p=parameter.toLocal8Bit();
    QByteArray a,b;
    a=c+p;
    b=a.toBase64();
    return QString::fromStdString(b.toStdString());
}
static QString protocol_decode(QString data){
    QByteArray r=data.toLocal8Bit();
    return QString::fromStdString(QByteArray::fromBase64(r).toStdString());
}
void network::readyread() {
    int id;
    id=rid;
    if (isfinished.contains(rid))
    {
        isfinished[rid]=true;
    }
    if (isfinished[rid])
    {
        while(mapbackvalue.contains(rid))
        {
            rid++;
            id=rid;
        }
        this->hide();
        ui->status->setText("GotReply");
        QString r=socket->readAll();
        if (r.mid(r.length()-1)=='\u0004')
        {
            isfinished[rid]=true;
            mapbackvalue[rid].append(r.left(r.length()-1));
            mapwaitreply[rid].quit();
        }
        else
        {
            isfinished[rid]=false;
            mapbackvalue[rid].append(r);
        }
    }
    else
    {
        QString r=socket->readAll();
        if (r.mid(r.length()-1)=='\u0004')
        {
            isfinished[rid]=true;
            mapbackvalue[rid].append(r.left(r.length()-1));
            mapwaitreply[rid].quit();
        }
        else
        {
            isfinished[rid]=false;
            mapbackvalue[rid].append(r);
        }
    }
}
QString network::request(QString data) {
    int id;
    id=sid;
    while(mapwaitreply.contains(sid))
    {
        sid++;
        id=sid;
    }
    QEventLoop waitforreply;
    mapwaitreply.insert(id, (const QEventLoop*)&waitforreply);
    ui->status->setText("Send...");
    socket->write(data.toLatin1());
    socket->write("\r\n");
    socket->flush();
    ui->status->setText("wait for server");
    waitforreply.exec();
    return mapbackvalue[sid];
}

