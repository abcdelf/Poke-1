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
    QString recdata=net->request("chat_num");
    allprintfed=recdata.toInt();
    //std::cout<<allprintfed<<std::endl;
    QObject::connect(getdata, SIGNAL(timeout()), this, SLOT(update()));
    getdata->start(1000);
}
void ChatScreen::on_pushButton_clicked()
{
    ui->pushButton->hide();
    net->request("chat_send "+ui->msgsend->document()->toPlainText());
    ui->msgsend->clear();    
}
void ChatScreen::update() {
    getdata->stop();
    QString recdata=net->request("chat_data "+QString::number(allprintfed)),addtmp;
    std::vector<std::string> datamap,minimap;
    SplitString(recdata.toStdString(),datamap,"$");
    int allnow=atoi(datamap[0].c_str());
    //std::cout<<allprintfed<<"-"<<datamap[allprintfed-1]<<std::endl;
    //std::cout<<recdata.toStdString()<<std::endl<<datamap[0]<<std::endl;
    while(allprintfed<allnow)
    {
        //std::cout<<allprintfed<<"-"<<datamap[allprintfed]<<std::endl;
        SplitString(datamap[allnow-allprintfed],minimap,"#");
        //std::cout<<datamap[allnow-allprintfed]<<"%"<<std::endl;
        allprintfed++;
        addtmp=addtmp+QString::fromStdString(minimap[0])+":"+QString::fromStdString(minimap[1])+"\n";
        //std::cout<<allnow<<"-"<<allprintfed<<"-"<<allprintfed<<"-"<<(QString::fromStdString(minimap[0])+":"+QString::fromStdString(minimap[1])+"\n").toStdString()<<std::endl;
        minimap.clear();
    }
    if (addtmp!="")
    {
        ui->msgshow->setText(ui->msgshow->document()->toPlainText()+addtmp);
        ui->msgshow->moveCursor(QTextCursor::End);
    }
    ui->pushButton->show();
    getdata->start(1000);
}

void ChatScreen::closeEvent(QCloseEvent *event)
{
    event->accept();
    getdata->stop();
}

