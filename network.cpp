#include "network.h"
#include "ui_network.h"
network::network(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::network)
{
    ui->setupUi(this);
    ui->status->setText("Init...");
    client=new QTcpSocket;
    //lock=new QEventLoop;
    //islock=new QEventLoop;
    ui->status->setText("Init!");
}

network::~network()
{
    client->disconnect();
    delete ui;
}
bool network::connecttoserver() {
    ui->status->setText("connecting...");
    client->connectToHost("o.starfiles.tk", 8863);
    QCoreApplication::processEvents();
    if (!client->waitForConnected(50000))
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
        //QObject::connect(client, &QTcpSocket::readyRead, this->lock, &QEventLoop::it);
        QObject::connect(client, &QTcpSocket::disconnected, this, &network::error);
        QObject::connect(timeouttimer, SIGNAL(timeout()), this, SLOT(error()));
        #ifdef WIN32
        setWindowFlags(windowFlags() &~ Qt::WindowCloseButtonHint);
        #endif
    #ifdef LINUX
        gtk_window_set_deletable(GTK_WINDOW (window), FALSE);
    #endif
        //QObject::connect(client,QTcpSocket::error(), this, &network::error);
        //std::thread heart(heartpacket,this);
        //heart.detach();
        this->hide();
        return true;
    }
}
void network::networkrecv() {
//    timeouttimer->stop();
    maytimeoutnotice->stop();
    allrecid++;
    int recid=allrecid;
    this->hide();
    ui->status->setText("GotReply");
    recdata[recid]=QString(client->readAll());
    ui->status->setText("R:"+recdata[recid]);
    islock[recid]->quit();
    //needwait=false;
}
void network::networksend(QString data)
{
    ui->status->setText("Send...");
    client->write(data.toLatin1());
    client->flush();
    ui->status->setText("wait for server");
//    QObject::connect(timeouttimer, SIGNAL(timeout()), this, SLOT(error()));
    QObject::connect(maytimeoutnotice, SIGNAL(timeout()), this, SLOT(timeoutnotice()));
//    this->timeouttimer->start(50000);
    this->maytimeoutnotice->start(3000);
}
QString network::request(QString data,bool isshow) {
    if (data==""){return "";}
    allid++;
    int id=allid;
    islock[id]=new QEventLoop;
    if (isshow){this->show();}
    this->networksend(data);
    islock[id]->exec();
    QString tmp=recdata[id];
    recdata[id].clear();
    if (isshow){this->hide();}
    return tmp;
}
/*
std::string network::request(std::string data,bool isshow){
    if (data==""){return "";}
    if (needwait){islock->exec();}
    needwait=true;
    if (isshow){this->show();}
    this->networksend(QString::fromStdString(data));
    lock->exec();
    QString tmp=reply;
    reply.clear();
    if (isshow){this->hide();}
    needwait=false;
    islock->quit();
    return tmp.toStdString();
}*/
void network::error() {
//    timeouttimer->stop();
//    maytimeoutnotice->stop();
    QMessageBox::information(NULL, "Network", "Server Disconnected", QMessageBox::Yes, QMessageBox::Yes);
    this->hide();
    std::terminate();
}
/*
static void heartpacket(network *net){
    while(1)
    {
        net->timeouttimer->start(5000);
        if (net->request("heartbeat")!="")
        {
            net->timeouttimer->stop();
        }
        else
        {
            net->timeouttimer->stop();
            net->timeouttimer->start(0);
            //emit net->timeouttimer->timeout();
        }
    }
}*/
void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length())
        v.push_back(s.substr(pos1));
}
void network::timeoutnotice(){
    maytimeoutnotice->stop();
    this->show();
}
