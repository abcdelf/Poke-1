#ifndef HELPCHOOSE_H
#define HELPCHOOSE_H

#include <QDialog>
#include "needhelp.h"
#include "helpothers.h"
#include "network.h"
namespace Ui {
class helpchoose;
}

class helpchoose : public QDialog
{
    Q_OBJECT

public:
    explicit helpchoose(QWidget *parent = 0);
    ~helpchoose();
    network *net;
private slots:
    void on_needhelp_clicked();

    void on_helpother_clicked();

private:
    Ui::helpchoose *ui;
};

#endif // HELPCHOOSE_H
