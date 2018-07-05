#ifndef POKE_H
#define POKE_H

#include <QMainWindow>

namespace Ui {
class Poke;
}

class Poke : public QMainWindow
{
    Q_OBJECT

public:
    explicit Poke(QWidget *parent = 0);
    ~Poke();

private:
    Ui::Poke *ui;
};

#endif // POKE_H
