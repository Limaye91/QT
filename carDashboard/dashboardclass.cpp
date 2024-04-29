#include "dashboardclass.h"
#include "./ui_dashboardclass.h"

DashBoardClass::DashBoardClass(QWidget *parent)
    : QMainWindow(parent),
    serviceptr(new serviceConnection)
    , ui(new Ui::DashBoardClass)
{
    ui->setupUi(this);
}

DashBoardClass::~DashBoardClass()
{
    delete ui;
    delete serviceptr;
    delete maindashboardptr;
}

void DashBoardClass::on_userprefbtn_clicked()
{
    userdialogptr = new userDialog(this);

    connect(this,&DashBoardClass::alloperator,userdialogptr,&userDialog::users);
    emit alloperator(serviceptr->getallinserivce());
     userdialogptr->show();
    connect(userdialogptr,&userDialog::userfromuserdialog,this,&DashBoardClass::getuser);
    // connect(serviceptr,&serviceConnection::newUserAdded,this,&DashBoardClass::newuseradded);
    connect(userdialogptr,&userDialog::setting,this,&DashBoardClass::set);


}




void DashBoardClass::on_dashboard_clicked()
{
    maindashboardptr=new maindashboard1();
    connect(this,&DashBoardClass::lastuser,maindashboardptr,&maindashboard1::lastusermain);
    emit lastuser(serviceptr->getlastuser());
    maindashboardptr->show();
    connect(maindashboardptr,&maindashboard1::lastsignal,this,&DashBoardClass::updateKmEngine);
}



void DashBoardClass::updateKmEngine(int Km,int EngineHr,int Fuel){
    serviceptr->UpdateKmEngine(Km,EngineHr,Fuel);
}










void DashBoardClass::getuser(QString user)
{
    QString name=user;
    serviceptr->setusername(name);
    emit alloperator(serviceptr->getallinserivce());
}

// void DashBoardClass::newuseradded(QString val)
// {
//     userdialogptr->updateusercombo(val);
// }

void DashBoardClass::set(std::vector<std::string>v)
{
    serviceptr->setusersetting(v);
    emit alloperator(serviceptr->getallinserivce());
}


void DashBoardClass::on_resetbtn_clicked()
{
    serviceptr->resetfucntion();
}

