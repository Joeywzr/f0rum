#ifndef POSTWINDOW_H
#define POSTWINDOW_H

#include <QMainWindow>

namespace Ui {
class Postwindow;
}

class Postwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Postwindow(QWidget *parent = 0);
    ~Postwindow();

private:
    Ui::Postwindow *ui;
};

#endif // POSTWINDOW_H
