#include "network.h"
#include "ui_network.h"
network::network(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::network)
{
    ui->setupUi(this);
    ui->status->setText("Init...");
    client=new QTcpSocket;
    lock=new QEventLoop;
    ui->status->setText("Init!");
}

network::~network()
{
    client->disconnect();
    delete ui;
}
bool network::connecttoserver() {
    ui->status->setText("onnecting...");
    client->connectToHost("23.235.133.143", 8863);
    QCoreApplication::processEvents();
    if (!client->waitForConnected(3000))
    {
        ui->status->setText("Falled!");
        client->disconnect();
        QMessageBox::critical(NULL, "Error", "Falled to connect to server", QMessageBox::Yes, QMessageBox::Yes);
        this->hide();
        std::terminate();
        return false;
    }
    else
    {
        ui->status->setText("Success!");
        QObject::connect(client, &QTcpSocket::readyRead, this, &network::networkrecv);
        QObject::connect(client, &QTcpSocket::readyRead, this->lock, &QEventLoop::quit);
        QObject::connect(client, &QTcpSocket::disconnected, this, &network::error);
        //QObject::connect(client, SIGNAL(QTcpSocket::error()), this, &network::error);
        this->hide();
        return true;
    }
}
void network::networkrecv() {
    timeouttimer->stop();
    ui->status->setText("GotReply");
    reply=QString(client->readAll());
    ui->status->setText("R:"+reply);
}
void network::networksend(QString data)
{
    ui->status->setText("Send...");
    client->write(data.toLatin1());
    client->flush();
    ui->status->setText("sent!");
    QObject::connect(timeouttimer, SIGNAL(timeout()), this, SLOT(error()));
    this->timeouttimer->start(8000);
}
QString network::request(QString data,bool isshow) {
    if (isshow)
    {this->show();}
    this->networksend(data);
    lock->exec();
    QString tmp=reply;
    reply.clear();
    if (isshow){this->hide();}
    return tmp;
}
std::string network::request(std::string data,bool isshow){
    if (isshow){this->show();}
    this->networksend(QString::fromStdString(data));
    lock->exec();
    QString tmp=reply;
    reply.clear();
    if (isshow){this->hide();}
    return tmp.toStdString();
}
void network::error() {
    QMessageBox::critical(NULL, "Error", "Server Disconnected", QMessageBox::Yes, QMessageBox::Yes);
    this->hide();
    std::terminate();
}
