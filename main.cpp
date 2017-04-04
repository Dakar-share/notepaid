#include "mainwindow.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
//it is notepaid project @
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/images/screen/timg.jpg");
    QSplashScreen splash(pixmap);
    splash.show();
    for(long i=0;i<90000000;i++);
    MainWindow w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
