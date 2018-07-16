#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H
#include <QMediaPlayer>
#include <QWidget>
#include <QMediaPlaylist>
#include <QCloseEvent>
#include "network.h"
namespace Ui {
class MediaPlayer;
}

class MediaPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit MediaPlayer(QWidget *parent = 0);
    ~MediaPlayer();
    bool isplaying=false;
    QMediaPlaylist *playlist;
    network *net;
private slots:
    void on_play_clicked();
    void on_pause_clicked();
    void on_listupdate_clicked();
    void on_volume_valueChanged(int value);
    void on_add_clicked();
    void on_clearlist_clicked();
    void on_next_clicked();
    void mediachanged();
    void on_previous_clicked();
    void playedtimechange();
    void on_playside_sliderReleased();

    void on_playside_sliderPressed();

private:
    void closeEvent(QCloseEvent * event);
    QMediaPlayer *mediaPlayer;
    Ui::MediaPlayer *ui;
    QString songLink="http://music.163.com/song/media/outer/url?id=";
};

#endif // MEDIAPLAYER_H
