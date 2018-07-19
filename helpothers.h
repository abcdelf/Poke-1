#ifndef HELPOTHERS_H
#define HELPOTHERS_H

#include <QWidget>

namespace Ui {
class helpothers;
}

class helpothers : public QWidget
{
    Q_OBJECT

public:
    explicit helpothers(QWidget *parent = 0);
    ~helpothers();

private:
    Ui::helpothers *ui;
};

#endif // HELPOTHERS_H
