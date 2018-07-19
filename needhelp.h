#ifndef NEEDHELP_H
#define NEEDHELP_H

#include <QWidget>
#include <QTimer>
#include "network.h"
namespace Ui {
class needhelp;
}

class needhelp : public QWidget
{
    Q_OBJECT

public:
    explicit needhelp(QWidget *parent = 0);
    ~needhelp();
    network *net;
    QString id;
    void init();
private slots:
    void requestloop();
private:
    QTimer waitloop;
    Ui::needhelp *ui;
};

#endif // NEEDHELP_H
