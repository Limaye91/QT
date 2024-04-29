#include "adduserdialog.h"
#include "ui_adduserdialog.h"

addUserDialog::addUserDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addUserDialog)
{
    ui->setupUi(this);
}

addUserDialog::~addUserDialog()
{
    delete ui;
}

void addUserDialog::on_adduserbtn_clicked()
{
    QString newuser = ui->addusertext->toPlainText();
    emit userfromadduser(newuser);
}

