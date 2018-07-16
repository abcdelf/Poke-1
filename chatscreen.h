#ifndef CHATSCREEN_H
#define CHATSCREEN_H
#include <QTimer>
#include <QWidget>
#include "network.h"
#include <QCloseEvent>
#include <iostream>
namespace Ui {
class ChatScreen;
}

class ChatScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ChatScreen(QWidget *parent = 0);
    ~ChatScreen();
    network *net;
    void joinchat();
    int allprintfed;
    QTimer *getdata;
public slots:
    void terminate_chatscreen();
private slots:
    void update();
    void on_pushButton_clicked();

private:
    void closeEvent(QCloseEvent *event);
    Ui::ChatScreen *ui;
};

#endif // CHATSCREEN_H
