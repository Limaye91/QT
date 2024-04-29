#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QLabel"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     this->setStyleSheet("background-color: #d4d4d1;");
    ap=new api;
    //QHeaderView *horizontalHeader = ui->FilterTable->horizontalHeader();
    //horizontalHeader->setStyleSheet("background-color: #ffffff; color: #000000;");

   // QHeaderView *verticalHeader = ui->FilterTable->verticalHeader();
    //verticalHeader->setStyleSheet("background-color: #ffffff; color: #000000;");

    ui->FilterTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Disable vertical scrollbar
    ui->FilterTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->FluidTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Disable vertical scrollbar
    ui->FluidTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    load();


    timer = new QTimer();

    timer->setInterval(1000);
    timer->setSingleShot(false);

    connect(timer, &QTimer::timeout,this, &MainWindow::handleValueChange);

    timer->start();

}



void MainWindow::load(){

    std::vector<Filter_details*> filterList = Filter_details::FilterList;

    int rowsCountFilter = filterList.size();
    ui->FilterTable->setRowCount(rowsCountFilter);

    for(int i=0; i<rowsCountFilter; i++){
        QTableWidgetItem *filterListItem =  new QTableWidgetItem(filterList[i]->getName());
        filterListItem->setTextAlignment(Qt::AlignCenter);
        ui->FilterTable->setItem(i,0,filterListItem);
        QDate currentDate = filterList[i]->getCurrentDate();
        QString dateString = currentDate.toString("dd-MM-yyyy");
  qDebug()<<"fILTER "<<dateString;
        QTableWidgetItem *dateTableItem = new QTableWidgetItem(dateString);
        dateTableItem->setTextAlignment(Qt::AlignCenter);
        ui->FilterTable->setItem(i,2,dateTableItem);
        loadStatus(i, 1, "good");
    }

    std::vector<Fluid_details*> fluidList = Fluid_details::FluidList;

    int rowsCountFluid = fluidList.size();
    ui->FluidTable->setRowCount(rowsCountFluid);

    for(int i=0; i<rowsCountFluid; i++){
        QTableWidgetItem *fluidListItem =  new QTableWidgetItem(fluidList[i]->getName());
        fluidListItem->setTextAlignment(Qt::AlignCenter);
        ui->FluidTable->setItem(i,0,fluidListItem);
        QDate currentDate = fluidList[i]->getCurrentDate();
        QString dateString = currentDate.toString("dd-MM-yyyy");
        qDebug()<<"fluid "<<dateString;

        QTableWidgetItem *dateTableItem = new QTableWidgetItem(dateString);
        dateTableItem->setTextAlignment(Qt::AlignCenter);
        ui->FluidTable->setItem(i,2,dateTableItem);

        loadStatus(i, 1, "good");
    }
}

void MainWindow::handleValueChange(){
    if(count == 0) timer->stop();
    std::vector<Filter_details*>& filterList = Filter_details::FilterList;
    for(int i=0; i<filterList.size(); i++){
        //qDebug()<<filterList[i]->getStatus();
        filterList[i] = filterList[i]->setStatus(i+1);
        int healthLevel = filterList[i]->getStatus();
        // qDebug()<<healthLevel;

        if(healthLevel > 80) loadStatus(i, 1, "good");
        else if(healthLevel > 50 && healthLevel < 80) loadStatus(i, 1, "warning");
        else if(healthLevel > 0 && healthLevel < 50)loadStatus(i, 1, "critical");
    }

    std::vector<Fluid_details*>& fluidList = Fluid_details::FluidList;
    for(int i=0; i<fluidList.size(); i++){
        //qDebug()<<fluidList[i]->getStatus();
        fluidList[i] = fluidList[i]->setStatus(i+1);
        int healthLevel = fluidList[i]->getStatus();
        // qDebug()<<healthLevel;

        if(healthLevel > 80) loadStatus(i, 1, "good");
        else if(healthLevel > 50 && healthLevel < 80) loadStatus(i, 1, "warning");
        else if(healthLevel > 0 && healthLevel < 50)loadStatus(i, 1, "critical");
    }

    count--;
}

void MainWindow::loadStatus(int row, int column, QString status){
    QWidget *widget = new QWidget();
    QHBoxLayout *hBoxLayout = new QHBoxLayout();
    QLabel *label1 = new QLabel();
    QLabel *label2 = new QLabel();
    QLabel *label3 = new QLabel();
    hBoxLayout->addWidget(label1);
    //hBoxLayout->addWidget(label3);
    hBoxLayout->addWidget(label2);
    widget->setLayout(hBoxLayout);

    QWidget *widget1 = new QWidget();
    QHBoxLayout *hBoxLayout1 = new QHBoxLayout();
    QLabel *label1Fluid = new QLabel();
    QLabel *label2Fluid = new QLabel();
    hBoxLayout1->addWidget(label1Fluid);
    hBoxLayout1->addWidget(label2Fluid);
    widget1->setLayout(hBoxLayout1);


    ui->FilterTable->setCellWidget(row, column, widget);
    ui->FluidTable->setCellWidget(row,column,widget1);
    int width = 50;
    int height = 50;

    label1->setFixedSize(width, height);
 label1Fluid->setFixedSize(width, height);

    if(status == "good"){
        QPixmap pixmap(":/check-mark_5299048.png");
        label2->setText("Good ");
        label2Fluid->setText("Good");
        if (!pixmap.isNull()) {
            label1->setPixmap(pixmap);
            label1->setScaledContents(true);

            label1Fluid->setPixmap(pixmap);
            label1Fluid->setScaledContents(true);
        } else {
            label1->setText("Image not found");
            label1Fluid->setText("Image not found");
        }
    }

    if(status == "warning"){
        QPixmap pixmap(":/warning_5067704 (1).png");
        label2->setText("Warning ");

        label2Fluid->setText("Warning");

        if (!pixmap.isNull()) {
            label1->setPixmap(pixmap);
            label1->setScaledContents(true);

            label1Fluid->setPixmap(pixmap);
            label1Fluid->setScaledContents(true);

        } else {
            label1->setText("Image not found");
            label1Fluid->setText("Image not found");
        }
    }

    if(status == "critical"){
        QPixmap pixmap(":/warning_564619.png");
        label2->setText("Critical ");
        label2Fluid->setText("Critical ");

        if (!pixmap.isNull()) {
            label1->setPixmap(pixmap);
            label1->setScaledContents(true);

            label1Fluid->setPixmap(pixmap);
            label1Fluid->setScaledContents(true);

        } else {
            label1->setText("Image not found");
            label1Fluid->setText("Image not found");
        }
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_FilterButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_FluidButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

