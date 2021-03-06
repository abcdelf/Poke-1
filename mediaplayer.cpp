#include "mediaplayer.h"
#include "ui_mediaplayer.h"
MediaPlayer::MediaPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaPlayer)
{
    ui->setupUi(this);
    mediaPlayer = new QMediaPlayer(this);
    playlist=new QMediaPlaylist;
    connect(mediaPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(mediachanged()));
    connect(mediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(playedtimechange()));
}

MediaPlayer::~MediaPlayer()
{
    delete ui;
}

void MediaPlayer::on_play_clicked()
{
    mediaPlayer->play();
}

void MediaPlayer::on_pause_clicked()
{
    mediaPlayer->pause();
}
void MediaPlayer::closeEvent(QCloseEvent * event)
{
    event->accept();
    mediaPlayer->stop();
    delete mediaPlayer;
    this->deleteLater();
}

void MediaPlayer::on_listupdate_clicked()
{
    ui->playlist->clear();
    playlist->clear();
    QString list=net->request("musicplaylist163");
    std::vector<std::string> listmap;
    SplitString(list.toStdString(),listmap,"$");
    for(int x=0;x<=((int)listmap.size()-1);x++)
    {
        ui->playlist->append(QString::fromStdString(listmap[x]));
        playlist->addMedia(QMediaContent(QUrl(songLink+QString::fromStdString(listmap[x]))));
    }
    mediaPlayer->setPlaylist(playlist);
    this->on_play_clicked();
}

void MediaPlayer::on_volume_valueChanged(int value)
{
    mediaPlayer->setVolume(value);
}

void MediaPlayer::on_add_clicked()
{
    net->request("musicplaylistadd163"+net->FUHAO+ui->musicid->text());
    //this->on_listupdate_clicked();
}

void MediaPlayer::on_clearlist_clicked()
{
    net->request("musicplaylistclear163");
    //this->on_listupdate_clicked();
}


void MediaPlayer::on_next_clicked()
{
    playlist->next();
    this->on_play_clicked();
}
void MediaPlayer::mediachanged(){
    ui->musicinfo->clear();
    if (mediaPlayer->isMetaDataAvailable())
    {
        ui->musicinfo->append(mediaPlayer->metaData(QString("Title")).toString());
        ui->musicinfo->append(mediaPlayer->metaData(QString("ContributingArtist")).toString());
    }
    else
    {
        ui->musicinfo->setText("No Music Data Available");
    }
    ui->playside->setRange(0,mediaPlayer->duration());
    int ma=QString::number(mediaPlayer->duration()/60000,10,1).toInt();
    int sa=(mediaPlayer->duration()-(ma*60000))/1000;
    int m=QString::number(mediaPlayer->position()/60000,10,1).toInt();
    int s=(mediaPlayer->position()-(m*60000))/1000;
    ui->TIME->setText(QString::number(m)+":"+QString::number(s)+"/"+QString::number(ma)+":"+QString::number(sa));
}

void MediaPlayer::on_previous_clicked()
{
    playlist->previous();
    this->on_play_clicked();
}
void MediaPlayer::playedtimechange() {
    ui->playside->setValue(mediaPlayer->position());
    int ma=QString::number(mediaPlayer->duration()/60000,10,1).toInt();
    int sa=(mediaPlayer->duration()-(ma*60000))/1000;
    ma=sa/60;
    sa=sa-(ma*60);
    int m=QString::number(mediaPlayer->position()/60000,10,1).toInt();
    int s=(mediaPlayer->position()-(m*60000))/1000;
    m=s/60;
    s=s-(m*60);
    //ui->musicinfo->setText(QString::number(mediaPlayer->position()));
    ui->TIME->setText(QString::number(m)+":"+QString::number(s)+"/"+QString::number(ma)+":"+QString::number(sa));
}

void MediaPlayer::on_playside_sliderReleased()
{
    mediaPlayer->setPosition(ui->playside->value());
    connect(mediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(playedtimechange()));
}

void MediaPlayer::on_playside_sliderPressed()
{
    mediaPlayer->disconnect(SIGNAL(positionChanged(qint64)));
}
