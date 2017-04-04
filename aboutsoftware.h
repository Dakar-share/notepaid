#ifndef ABOUTSOFTWARE_H
#define ABOUTSOFTWARE_H

#include <QMainWindow>
#include <QMovie>
#include <QDebug>
#include <QLabel>
#include <QDir>
namespace Ui {
class aboutsoftware;
}

class aboutsoftware : public QMainWindow
{
    Q_OBJECT

public:
    explicit aboutsoftware(QWidget *parent = 0);
    ~aboutsoftware();

private:
    Ui::aboutsoftware *ui;
    QMovie *movie;
    unsigned int index;
    QSize size;
private slots:
    void nextMovieSlot();
};

#endif // ABOUTSOFTWARE_H
