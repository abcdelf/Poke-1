#ifndef HELPOTHERS_H
#define HELPOTHERS_H

#include <QWidget>
#include <network.h>
namespace Ui {
class helpothers;
}

class helpothers : public QWidget
{
    Q_OBJECT

public:
    explicit helpothers(QWidget *parent = 0);
    ~helpothers();
    network *net;
private slots:
    void on_gohelp_clicked();

    void on_send_clicked();

private:
    Ui::helpothers *ui;
};

#endif // HELPOTHERS_H
