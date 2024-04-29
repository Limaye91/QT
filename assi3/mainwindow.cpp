#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QPdfWriter>
#include <QFileDialog>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include "QTextDocumentWriter"
#include "QTextDocument"
#include "QDesktopServices"
#include <QVector>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QPixmap pixmap("/home/kasturi/Pictures/Screenshots/man.png");
    ui->imageLable->setPixmap(pixmap);
    ui->imageLable->setScaledContents(true);
    setComboBox();
    foldptr=new fold;

   // connect(this,&MainWindow::updateMap,&foldptr, &fold::insertData);
    // connect(this, SIGNAL(updateMap(const QVector<QString>&)), foldptr, SLOT(insertData(const QVector<QString>&)));
    connect(this, &MainWindow::updateMap, foldptr, &fold::insertData);
    connect(this, &MainWindow::removedata, foldptr, &fold::removeData);

    //connect(this, SIGNAL(updateMap(QVector<QString>)), foldptr, SLOT(insertData(QVector<QString>)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setComboBox()
{
    ui->comboBox->addItem("Mumbai");
    ui->comboBox->addItem("pune");
    ui->comboBox->addItem("Banglore");
}

void MainWindow::on_pushButton_clicked()
{
    imgPath=QFileDialog::getOpenFileName(this,"select an image",QDir::homePath(),"Image Files(*.png *.jpg *.jpeg)");
    if(!imgPath.isEmpty())
    {
        QFileInfo file_Info(imgPath);
        QString File_Name=file_Info.fileName();


        ui->pushButton->setText(File_Name);
        QImage image(imgPath);
        if(!image.isNull())
        {
            ui->imageLable->setPixmap(QPixmap::fromImage(image));
            ui->imageLable->setScaledContents(true);

        }
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QString Device_name=ui->Dname->toPlainText();
    QString Serial_no=ui->Sno->toPlainText();
    QString Assigned=ui->Ass->toPlainText();
    QString Location=ui->comboBox->currentText();
    QVector<QString> v={Device_name,Serial_no,Assigned,Location,imgPath};
    emit updateMap(v);








    // if(imgPath.size() != 0)
    //     mp[Device_name].push_back({Serial_no,{Assigned,{Location,imgPath}}});
    // else
    //     mp[Device_name].push_back({Serial_no,{Assigned,{Location,"#"}}});

    // qDebug()<<mp.size();


}


void MainWindow::on_pushButton_3_clicked()
{
    QString Device_name=ui->Dname->toPlainText();
    // if(foldptr->mp.find(Device_name)==foldptr->mp.end())
    //     {
    //         qDebug()<<"deivce is not present";
    //         return;
    //     }
    QString fileName = QFileDialog::getSaveFileName(this, tr("save pdf"), "output.pdf", tr("PDF Files (*.pdf)"));
        if(fileName.isEmpty())
        {
            return;
        }
        QTextDocument document;
        QTextCursor cursor(&document);

        QString serial = ui->Sno->toPlainText();
        for(int i = 0 ; i < foldptr->mp[Device_name].size() ; i++)
        {
            if(foldptr->mp[Device_name][i].first == serial)
            {
                cursor.insertText("Deivce Name : " + Device_name + "\n");
                cursor.insertText("Serial Number : " + foldptr->mp[Device_name][i].first + "\n");
                cursor.insertText("Assigned : " + foldptr->mp[Device_name][i].second.first + "\n");
                cursor.insertText("Location : " + foldptr->mp[Device_name][i].second.second.first + "\n");
                if(foldptr->mp[Device_name][i].second.second.second != "#")
                {
                    QTextImageFormat img;
                    img.setName(imgPath);
                    cursor.insertImage(img);
                }
                else{

                    QTextImageFormat img;
                    img.setName("/home/kasturi/Pictures/Screenshots/man.png");
                    cursor.insertImage(img);


                }
            }

        }


        QPdfWriter pdfWriter(fileName);
        pdfWriter.setResolution(300);
        QPainter pdff (&pdfWriter);
        document.drawContents(&pdff);
        QDesktopServices::openUrl(QUrl:: fromLocalFile(fileName));
}



void MainWindow::on_removeButton_clicked()
{
    QString Serial_no=ui->Sno->toPlainText();
    emit removedata(Serial_no);
}


void MainWindow::on_newWindow_clicked()
{
    newdialog=new Dialog();
    newdialog->show();

}

