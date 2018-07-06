#include "chatscreen.h"
#include "ui_chatscreen.h"

ChatScreen::ChatScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatScreen)
{
    ui->setupUi(this);
}

ChatScreen::~ChatScreen()
{
    getdata->stop();
    delete ui;
}
void ChatScreen::joinchat(){
    getdata=new QTimer;
    QString recdata=net->request("chat_data");
    std::vector<std::string> datamap;
    SplitString(recdata.toStdString(),datamap,"$");
    allprintfed=atoi(datamap[0].c_str());
    //std::cout<<allprintfed<<std::endl;
    QObject::connect(getdata, SIGNAL(timeout()), this, SLOT(update()));
    getdata->start(1000);
}
void ChatScreen::on_pushButton_clicked()
{
    net->request("chat_send "+ui->msgsend->document()->toPlainText());
    ui->msgsend->clear();
}
void ChatScreen::update() {
    getdata->stop();
    QString recdata=net->request("chat_data"),addtmp;
    std::vector<std::string> datamap,minimap;
    SplitString(recdata.toStdString(),datamap,"$");
    int allnow=atoi(datamap[0].c_str());
    while(allprintfed<allnow)
    {
        allprintfed++;
        SplitString(datamap[allprintfed],minimap,"#");
        addtmp=addtmp+QString::fromStdString(minimap[0])+":"+QString::fromStdString(minimap[1])+"\n";
        //std::cout<<allnow<<"-"<<allprintfed<<"-"<<allprintfed<<"-"<<(QString::fromStdString(minimap[0])+":"+QString::fromStdString(minimap[1])+"\n").toStdString()<<std::endl;
        minimap.clear();
    }
    ui->msgshow->setText(ui->msgshow->document()->toPlainText()+addtmp);
    getdata->start(1000);
}

void ChatScreen::closeEvent(QCloseEvent *event)
{
    event->accept();
    getdata->stop();
}

