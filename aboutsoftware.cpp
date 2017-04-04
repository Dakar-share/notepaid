#include "aboutsoftware.h"
#include "ui_aboutsoftware.h"

aboutsoftware::aboutsoftware(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::aboutsoftware)
{
    ui->setupUi(this);
    this->movie = new QMovie(":/Gif/images/gif/xhr.gif");
    qDebug()<<QDir::currentPath();
    qDebug()<<"current movie has "<<this->movie->frameCount();
    ui->moveLabel->setMovie(this->movie);
    this->movie->start();
    this->index = 0;
    QObject::connect(ui->startButton,SIGNAL(clicked()),this->movie,SLOT(start()));//connect & slot
    this->connect(ui->stopButton,SIGNAL(clicked()),this->movie,SLOT(stop()));//connnect signal & slot
    QObject::connect(ui->nextButton,SIGNAL(clicked()),this,SLOT(nextMovieSlot()));
}

aboutsoftware::~aboutsoftware()
{
    delete ui;
}

void aboutsoftware::nextMovieSlot()
{
    this->index++;
    delete this->movie;
    switch(this->index)
    {
         case 0:
             this->movie = new QMovie(":/Gif/images/gif/xhr.gif");
             qDebug()<<"index =0";
        break;
        case 1:
                this->movie = new QMovie(":/Gif/images/gif/zb.gif");
               qDebug()<<"index =1";
               break;
        default:
              this ->index = 0;
               this->movie = new QMovie(":/Gif/images/gif/xhr.gif");
              qDebug()<<"Default....";
    }
    ui->verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
    ui->moveLabel->setMovie(this->movie);
   this->movie->start();
   QObject::connect(ui->startButton,SIGNAL(clicked()),this->movie,SLOT(start()));//re connect & slot
   this->connect(ui->stopButton,SIGNAL(clicked()),this->movie,SLOT(stop()));//re connnect signal & slot
   qDebug()<<"current movie has "<<this->movie->frameCount();
    qDebug()<<"next...";
}
