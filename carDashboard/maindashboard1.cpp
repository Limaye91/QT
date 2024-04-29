#include "maindashboard1.h"
#include "ui_maindashboard1.h"

maindashboard1::maindashboard1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::maindashboard1)
{
    ui->setupUi(this);
    ui->leftlabel->setVisible(false);
      ui->rightlabel->setVisible(false);


    timer=new QTimer;
    connect(timer,&QTimer::timeout,this,&maindashboard1::Speedometer);
    timer->start(3000);

    fueltimer=new QTimer(this);
    connect(fueltimer,&QTimer::timeout,this,&maindashboard1::fuelslot);
    fueltimer->start(2000);
}

void maindashboard1::fuelslot()
{
    if(fuel_level>0)
    {
    fuel_level=fuel_level-1;
    qDebug()<<fuel_level;
    ui->progressBar->setValue(fuel_level);
    }

}

void maindashboard1::leftsignalslot()
{
    ui->leftlabel->setVisible(!ui->leftlabel->isVisible());
}

void maindashboard1::rightsignalslot()
{
    ui->rightlabel->setVisible(!ui->rightlabel->isVisible());
}
maindashboard1::~maindashboard1()
{
    delete ui;
    cal();
    emit lastsignal(DTotal_km,DTotal_Engine_hour,Dfuel_level);

}

void maindashboard1::cal(){
    DTotal_km=Total_km-DTotal_km;
    DTotal_Engine_hour=Total_Engine_hour-DTotal_Engine_hour;
    Dfuel_level= Dfuel_level-fuel_level ;
    // qDebug()<<DTotal_km<<DTotal_Engine_hour<<Dfuel_level;
}

void maindashboard1::Speedometer(){
    if(speed>=140){
        qDebug()<<"Max limit reached";
        //timer->stop();
    }
    qDebug()<<"printing timerrrr";
    ui->dial->setValue(speed);
    if(mode=="sports"){
        speed+=50;
    }
    else speed+=10;

    Total_Engine_hour+=1;
    Total_km+=50;
    //fuel_level-=1;
    ui->lcd_Engine->display(Total_Engine_hour);
    ui->lcd_Km->display(Total_km);
}





void maindashboard1::lastusermain(data1 *obj)
{
   color=obj->getTheme();
    {
        // Access the user theme value from the user settings object
        QString theme = obj->getTheme();

        // Set the background color based on the theme value
        if (theme == "dark") {
            // Set dark background color
            QPalette palette = this->palette();
            palette.setColor(QPalette::Window, QColor(Qt::black)); // Example: Dark background color
            this->setPalette(palette);
        } else {
            // Set light background color
            QPalette palette = this->palette();
            palette.setColor(QPalette::Window, QColor(Qt::white)); // Example: Light background color
            this->setPalette(palette);
        }
    }

    name=obj->getUsername();
    mode=obj->getMode();
    Total_km=obj->getTotalKilometers();
    Total_Engine_hour=obj->getEngineHours();
    fuel_level=obj->getFuelLevel();
    DTotal_km=Total_km;
    DTotal_Engine_hour=Total_Engine_hour;
    Dfuel_level=fuel_level;
    ui->lcd_Engine->display(Total_Engine_hour);
    ui->lcd_Km->display(Total_km);


}





void maindashboard1::on_leftbtn_clicked()
{
    if(ltimer && ltimer->isActive())
    {
        ltimer->stop();
        ui->leftlabel->setVisible(false);
    }
    else
    {
        if(rtimer && rtimer->isActive())
        {
            rtimer->stop();
            ui->rightlabel->setVisible(false);
        }
        ltimer=new QTimer(this);
        connect(ltimer,&QTimer::timeout,this,&maindashboard1::leftsignalslot);
        ltimer->setInterval(300);
        ltimer->start();

    }
}


void maindashboard1::on_rightbtn_clicked()
{
    if(rtimer && rtimer->isActive())
    {
        rtimer->stop();
        ui->rightlabel->setVisible(false);
    }
    else
    {
        if(ltimer && ltimer->isActive())
        {
            ltimer->stop();
            ui->leftlabel->setVisible(false);
        }
        rtimer=new QTimer(this);
        connect(rtimer,&QTimer::timeout,this,&maindashboard1::rightsignalslot);
        rtimer->setInterval(300);
        rtimer->start();

    }
}

