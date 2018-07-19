#ifndef POKE_H
#define POKE_H
#include "mediaplayer.h"
#include <QMainWindow>
#include "network.h"
#include "helpchoose.h"
#include "chatscreen.h"
namespace Ui {
class Poke;
}

class Poke : public QMainWindow
{
    Q_OBJECT

public:
    explicit Poke(QWidget *parent = 0);
    ~Poke();
    network *net;
private slots:
    void on_submit_clicked();

    void on_gochat_clicked();

    void on_gomedia_clicked();

    void on_help_clicked();

private:
    Ui::Poke *ui;
};

#endif // POKE_H
