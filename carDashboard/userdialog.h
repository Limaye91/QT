#ifndef USERDIALOG_H
#define USERDIALOG_H
#include "adduserdialog.h"
#include <QDialog>
#include"../data/data1.h"
namespace Ui {
class userDialog;
}

class userDialog : public QDialog
{
    Q_OBJECT

public:
    explicit userDialog(QWidget *parent = nullptr);
    ~userDialog();
    void setcomboboxes();
    void updateusercombo(QString val);
private slots:
    void on_adduserbtn_clicked();
    void getnewuser(QString);
    void on_setbtn_clicked();

public slots:
    void users(QVector<data1*>);
    void setUserSettingsForUser(const QString userName);
signals:
    void userfromuserdialog(QString);
    void setting(std::vector<std::string>);
    void newsetting(QVector<data1*>);

private:
    Ui::userDialog *ui;
    addUserDialog *adduserptr;
    QVector<data1*> usersVector;
};

#endif // USERDIALOG_H
