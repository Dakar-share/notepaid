#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("notepaid");
    QObject::connect(ui->newAction,SIGNAL(triggered()),this,SLOT(newFileSlot()));//new
    QObject::connect(ui->openAction,SIGNAL(triggered()),this,SLOT(openFileSlot()));//open
    QObject::connect(ui->saveAction,SIGNAL(triggered()),this,SLOT(saveFileSlot()));//save
    QObject::connect(ui->saveAsAction,SIGNAL(triggered()),this,SLOT(saveAsFileSlot()));//save as
    QObject::connect(ui->printAction,SIGNAL(triggered()),this,SLOT(printFileSlot()));//print
    QObject::connect(ui->printViewAction,SIGNAL(triggered()),this,SLOT(printViewSlot()));//print view
    QObject::connect(ui->printPdfAction,SIGNAL(triggered()),this,SLOT(printPdfSlot()));//print Pdf

    QObject::connect(ui->exitAction,SIGNAL(triggered()),this,SLOT(close()));//close()
    QObject::connect(ui->undoAction,SIGNAL(triggered()),ui->textEdit,SLOT(undo()));//undo
    QObject::connect(ui->redoAction,SIGNAL(triggered()),ui->textEdit,SLOT(redo()));//redo
    QObject::connect(ui->colorAction,SIGNAL(triggered()),ui->textEdit,SLOT(copy()));//copy
    QObject::connect(ui->pasteAction,SIGNAL(triggered()),ui->textEdit,SLOT(paste()));//paste
    QObject::connect(ui->cutAction,SIGNAL(triggered()),ui->textEdit,SLOT(cut()));//cut
    QObject::connect(ui->seletAllAction,SIGNAL(triggered()),ui->textEdit,SLOT(selectAll()));//selectAll


    QObject::connect(ui->fontAction,SIGNAL(triggered()),this,SLOT(setFontSlot()));
    QObject::connect(ui->colorAction,SIGNAL(triggered()),this,SLOT(setColorSlot()));
    QObject::connect(ui->timeAction,SIGNAL(triggered()),this,SLOT(currentDateTimeSlot()));
    QObject::connect(ui-> gitHubAction,SIGNAL(triggered()),this,SLOT(GithubSlot()));//github
    QObject::connect(ui->aboutQtAction,SIGNAL(triggered()),qApp,SLOT(aboutQt()));//about Qt
    QObject::connect(ui->aboutSoftWareAction,SIGNAL(triggered()),this,SLOT(aboutSoftwareSlot()));

    QObject::connect(ui->textEdit,SIGNAL(textChanged()),this,SLOT(changeEditSlot()));

}
void MainWindow::changeEditSlot()
{
  this->setWindowTitle("notepaid*");

}
void MainWindow::closeEvent(QCloseEvent *event)
{
  //event->ignore();//忽略关闭事件
  if(ui->textEdit->document()->isModified())
  {
      QMessageBox msgBox;
      msgBox.setText("The document has been modified.");
      msgBox.setInformativeText("Do you want to save your changes?");
      msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Save);
      int ret = msgBox.exec();//QDialog exec 执行返回一个值

      switch (ret) {
        case QMessageBox::Save:
            // Save was clicked
          this->saveFileSlot();
            break;
        case QMessageBox::Discard:
            // Don't Save was clicked
            event->accept();
            break;
        case QMessageBox::Cancel:
            // Cancel was clicked
            event->ignore();
            break;
        default:
            // should never be reached
            break;
      }

  }
  else
  {
      event->accept();//接收关闭事件
  }
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::newFileSlot()
{ //if textEdit is modified
    if(ui->textEdit->document()->isModified())
    {
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();//QDialog exec 执行返回一个值

        switch (ret) {
          case QMessageBox::Save:
              // Save was clicked
              this->saveFileSlot();
              break;
          case QMessageBox::Discard:
              // Don't Save was clicked
              ui->textEdit->clear();
              this->setWindowTitle("新建文件");
              break;
          case QMessageBox::Cancel:
              // Cancel was clicked
              break;
          default:
              // should never be reached
              break;
        }
        qDebug()<<"current file modified";
    }
    else
    {
        //qDebug()<<"no current";
        ui->textEdit->clear();
        this->setWindowTitle("新建文件");
    }
}

void MainWindow::openFileSlot()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath());//起始路径设置为当前路径currentPatch
    qDebug()<<"QFile Name:"<<fileName;
    if(fileName.isEmpty())
    {
        //QMessageBox::information(this,"Error Message","Please Select a File");
        return;
    }
    QFile *file = new QFile;
    file->setFileName(fileName);//set file name
    bool ok = file->open(QIODevice::ReadOnly);//open file ad read only mode
    if(ok)
    {
        QTextStream in(file);//file and file stream connect
        ui->textEdit->setText(in.readAll());//read all context from the file
        file->close();
        delete file;
    }
    else
    {
       QMessageBox::information(this,"Error Message","File Open Error"+file->errorString());
       return;
    }

}
void MainWindow::saveFileSlot()
{
    if(saveFileName.isEmpty())
    {
        this->saveAsFileSlot();
    }
    else
    {
        QFile *file = new QFile;
        file->setFileName(saveFileName);
        bool ok =file->open(QIODevice::WriteOnly);
        if(ok)
        {
            QTextStream out(file);
            this->setWindowTitle("notepaid");
            out<<ui->textEdit->toPlainText();//这里转换为纯文本
            file->close();
            delete file;
        }
        else
        {
            QMessageBox::information(this,"Error Message","Save fiald...");
            return;
        }

    }

}
void MainWindow::saveAsFileSlot()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save File",QDir::currentPath());
    //note:getSaveFileName
    if(fileName.isEmpty())
    {
        return;
    }
    else
    {
        if(saveFileName.isEmpty())
            saveFileName=fileName;
        QFile *file = new QFile;
        file->setFileName(fileName);
        bool ok =file->open(QIODevice::WriteOnly);
        if(ok)
        {
            QTextStream out(file);
            this->setWindowTitle("notepaid");
            out<<ui->textEdit->toPlainText();//这里转换为纯文本
            file->close();
            delete file;
        }
        else
        {
            QMessageBox::information(this,"Error Message","Save fiald...");
            return;
        }
    }

}
void MainWindow::printFileSlot()
{   // 创建打印机对象
    QPrinter printer;
    //QPrintDialog static member
    qDebug()<<"using QPrintDialog.....";

       // 创建打印对话框
    QPrintDialog dlg(&printer, this);

       //如果编辑器中有选中区域，则打印选中区域
    if (ui->textEdit->textCursor().hasSelection())
        dlg.addEnabledOption(QAbstractPrintDialog::PrintSelection);

       // 如果在对话框中按下了打印按钮，则执行打印操作
    if (dlg.exec() == QDialog::Accepted) {
           ui->textEdit->print(&printer);
       }

}
void MainWindow::printViewSlot()
{
    QPrinter printer;//创建打印机
    QPrintPreviewDialog preview(&printer,this);//创建打印预览对话框

    connect(&preview,SIGNAL(paintRequested(QPrinter*)),this,SLOT(printPreview(QPrinter*)));
    preview.exec();
}
void MainWindow::printPreview(QPrinter *printer)
{
    qDebug()<<"print view print.....";
    ui->textEdit->print(printer);
}
//print pdf
void MainWindow::printPdfSlot()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("导出PDF文件"),QString(),".pdf");
    if(!fileName.isEmpty())
    {
       if(QFileInfo(fileName).suffix().isEmpty())
           fileName.append(".pdf");
       QPrinter printer;
       printer.setOutputFormat(QPrinter::PdfFormat);
       printer.setOutputFileName(fileName);
       ui->textEdit->print(&printer);
    }
    else
    {
        return;
    }
}


void MainWindow::setColorSlot()
{
    /*
const QColorDialog::ColorDialogOptions options = QFlag(colorDialogOptionsWidget->value());
    const QColor color = QColorDialog::getColor(Qt::green, this, "Select Color", options);

    if (color.isValid()) {
        colorLabel->setText(color.name());
        colorLabel->setPalette(QPalette(color));
        colorLabel->setAutoFillBackground(true);
    }
    */
    QColor color = QColorDialog::getColor(Qt::red,this);
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
    }
    else
    {
     //QMessageBox::information(this,"Error Message","Color unValid");
     return;
    }
}
void MainWindow::currentDateTimeSlot()
{
    QDateTime current = QDateTime::currentDateTime();
    QString time  = current.toString("yyyy-M-dd hh:mm:ss");//QDateTime --->QString
    ui->textEdit->append(time);
}
void MainWindow::setFontSlot()
{
   /*
    * bool ok;
QFont font = QFontDialog::getFont(&ok, QFont("Times", 12), this);
if (ok) {
    // font is set to the font the user selected
} else {
    // the user canceled the dialog; font is set to the initial
    // value, in this case Times, 12.
}
    */
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if(ok)
    {
        ui->textEdit->setFont(font);
    }
    else
    {
       // QMessageBox::information(this,"Error Message","Error Set Font!!");
        return;

    }

}

void MainWindow::GithubSlot()
{
         QDesktopServices::openUrl(QUrl("https://github.com/Dakar-share/notepaid"));
}

void MainWindow::aboutSoftwareSlot()
{
    aboutsoftware *about = new aboutsoftware;//
    about->show();//unmodal dialog
    //about->exec();//modal dialog only dialog


}
