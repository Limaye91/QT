#ifndef DIALOG_H
#define DIALOG_H
#include "fold.h"
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    map<QString, QVector<std::pair<QString, std::pair<QString, std::pair<QString, QString>>>>>mp1;
    void importdata();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
    fold* f1;
    void setComboBox2();
};

#endif // DIALOG_H
