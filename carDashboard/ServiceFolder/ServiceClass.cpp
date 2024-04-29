#include "dashboardclass.h"
#include "./ui_dashboardclass.h"

DashBoardClass::DashBoardClass(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DashBoardClass)
{
    ui->setupUi(this);
}

DashBoardClass::~DashBoardClass()
{
    delete ui;
}
