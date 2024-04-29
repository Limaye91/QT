#ifndef MAINDASHBOARD1_H
#define MAINDASHBOARD1_H
#include "../data/data1.h"
#include <QDialog>
#include <QDebug>
#include <QPixmap>
#include <QTimer>
namespace Ui {
class maindashboard1;
}

class maindashboard1 : public QDialog
{
    Q_OBJECT

public:
    explicit maindashboard1(QWidget *parent = nullptr);
    ~maindashboard1();
    void cal();
public slots:
    void lastusermain(data1 * obj);
    void Speedometer();

private:
    Ui::maindashboard1 *ui;
    QString color;

    QTimer* timer;
    QTimer *fueltimer;
    QTimer *ltimer=nullptr;
    QTimer *rtimer=nullptr;
    int speed=0;
    QString name;
    QString mode;
    int Total_km;
    int Total_Engine_hour;
    int fuel_level;
    int DTotal_km;
    int DTotal_Engine_hour;
    int Dfuel_level;
signals:
     void lastsignal(int,int,int);

private slots:
     void fuelslot();
    void leftsignalslot();
     void rightsignalslot();

     void on_leftbtn_clicked();
     void on_rightbtn_clicked();
};

#endif // MAINDASHBOARD1_H
