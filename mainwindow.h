#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>

#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>

#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QDateTime>
#include <QMessageBox>

#include <QUrl>
#include <QDesktopServices>//using desktop service
#include <QCloseEvent>//当程序需要关闭的时候，要处理的内容
//事件都是受保护的成员函数
//QWidget closeEvent() QMain Window closeEvent()

#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPrinter>
#include "aboutsoftware.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString saveFileName;
protected:
    void closeEvent(QCloseEvent *);
private slots:
    void newFileSlot();//new
    void openFileSlot();//open file
    void saveFileSlot();//save
    void saveAsFileSlot();//save as
    void printFileSlot();//print
    void printViewSlot();//print view
    void printPreview(QPrinter*);
    void printPdfSlot();//print pdf
    void setFontSlot();//设置字体
    void setColorSlot();//设置字体颜色
    void currentDateTimeSlot();//获取当前时间
    void GithubSlot();//github  using default  website
    void aboutSoftwareSlot();//about software
    void changeEditSlot();
};

#endif // MAINWINDOW_H
