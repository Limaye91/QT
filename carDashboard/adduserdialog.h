#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>

namespace Ui {
class addUserDialog;
}

class addUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addUserDialog(QWidget *parent = nullptr);
    ~addUserDialog();

private slots:
    void on_adduserbtn_clicked();
signals:
    void userfromadduser(QString);

private:
    Ui::addUserDialog *ui;
};

#endif // ADDUSERDIALOG_H
