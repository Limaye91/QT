#ifndef DASHBOARDCLASS_H
#define DASHBOARDCLASS_H
#include "serviceconnection.h"
#include <QMainWindow>
#include "userdialog.h"
#include "maindashboard1.h"
// #include "../data/data.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class DashBoardClass;
}
QT_END_NAMESPACE

class DashBoardClass : public QMainWindow
{
    Q_OBJECT

public:
    DashBoardClass(QWidget *parent = nullptr);
    ~DashBoardClass();

signals:
     void lastuser(data1*);
    void alloperator(QVector<data1*>);

private slots:

    void on_userprefbtn_clicked();

    void on_dashboard_clicked();
    void getuser(QString);
    // void newuseradded(QString);
    void set(std::vector<std::string>);

    void updateKmEngine(int Km,int EngineHr,int Fuel);
    void on_resetbtn_clicked();

private:
    Ui::DashBoardClass *ui;
    serviceConnection *serviceptr;
    userDialog* userdialogptr;
    maindashboard1* maindashboardptr;

};
#endif // DASHBOARDCLASS_H
