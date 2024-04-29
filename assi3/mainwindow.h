#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMap>
#include <QVector>
#include <QMainWindow>
#include "fold.h"
#include "dialog.h"
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString imgPath;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void on_removeButton_clicked();

    void on_newWindow_clicked();

signals:
    QVector<QString> updateMap(QVector<QString>&v);
    QString removedata(const QString& serialno);
    //void sendData();

private:
    Ui::MainWindow *ui;
    Dialog * newdialog;
    fold *foldptr;
   //map <QString , vector <pair <QString,pair<QString , pair<QString , QString>>>>> mp;
    void setComboBox();
};
#endif // MAINWINDOW_H
