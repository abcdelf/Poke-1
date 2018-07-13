#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H
#include "network.h"
#include <QDialog>
#include <QApplication>
#include <QCloseEvent>
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
    bool islogined=false;
    QEventLoop *wait_login;
public slots:
    void terminate_loginscreen();
private slots:
    void on_go_clicked();
    void on_pushButton_clicked();
    void closeEvent(QCloseEvent *event);

private:
    Ui::loginscreen *ui;
};

#endif // LOGINSCREEN_H
