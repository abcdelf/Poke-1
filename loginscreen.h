#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H
#include "network.h"
#include <QDialog>
#include <QApplication>
namespace Ui {
class loginscreen;
}

class loginscreen : public QDialog
{
    Q_OBJECT

public:
    explicit loginscreen(QWidget *parent = 0);
    ~loginscreen();
    bool islogin=true;
    network *net;
    QEventLoop *wait_login;
private slots:
    void on_go_clicked();
    void on_pushButton_clicked();

private:
    Ui::loginscreen *ui;
};

#endif // LOGINSCREEN_H
