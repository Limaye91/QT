#include "userdialog.h"
#include "ui_userdialog.h"
#include <QDebug>
userDialog::userDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::userDialog)
{
    // qDebug()<<"hello";
    ui->setupUi(this);

}

userDialog::~userDialog()
{
    delete ui;
    delete adduserptr;
}



void userDialog::on_adduserbtn_clicked()
{
    adduserptr = new addUserDialog;
    adduserptr->show();
    connect(adduserptr,&addUserDialog::userfromadduser,this,&userDialog::getnewuser);
}

void userDialog::getnewuser(QString name)
{
    QString newuser=name;
    emit userfromuserdialog(newuser);
}

// void userDialog::users(QVector<data1*> users)
// {
// // {
// //     for (auto user : users) {
// //         ui->usernamecombo->addItem(user);
// //     }
// //     ui->themecombo->addItems({"dark","light"});
// //     ui->modecombo->addItems({"sports","normal"});
// //      connect(ui->usernamecombo, &QComboBox::currentTextChanged, this, [this, detailList](const QString& newText)
// // }

// ui->usernamecombo->clear();
//     ui->modecombo->clear();
//     ui->themecombo->clear();
//     for (const auto& detail : users) {
//         ui->usernamecombo->addItem(detail->getUsername());
//         // ui->Select_Mode->addItem(detail->GetMode_of_driving());
//         // ui->Select_Theme->addItem(detail->GetPrefered_color());
//         // Add more items to other UI elements as needed
//     }
//     ui->modecombo->addItems({"Sports", "Normal"});
//     ui->themecombo->addItems({"Dark", "Light"});
//     connect(ui->usernamecombo, &QComboBox::currentTextChanged, this, [this, users](const QString& newText) {
//         // Find the user details corresponding to the selected username
//         data1* selectedDetail = nullptr;
//         for (const auto& detail : users) {
//             if (detail->getUsername()== newText) {
//                 selectedDetail = detail;
//                 break;
//             }
//         }

//         // Update the mode and theme comboboxes based on the selected user
//         if (selectedDetail) {
//             ui->modecombo->setCurrentText(selectedDetail->getMode());
//             ui->themecombo->setCurrentText(selectedDetail->getTheme());
//         }
//     });

// }

void userDialog::users(QVector<data1*> usersList)
{
    usersVector = usersList;
    ui->usernamecombo->clear();
    ui->modecombo->clear();
    ui->themecombo->clear();

    for (auto detail : usersList) {

        ui->usernamecombo->addItem(detail->getUsername());
        qDebug()<<detail->getUsername();
    }

    ui->modecombo->addItems({"sports", "normal"});
    ui->themecombo->addItems({"dark", "light"});

    // connect(ui->usernamecombo, QOverload<const QString&>::of(&QComboBox::currentTextChanged), this, [this, &users](const QString& newText) {
    connect(ui->usernamecombo, &QComboBox::currentTextChanged, this,&userDialog::setUserSettingsForUser);

}

void userDialog::setUserSettingsForUser(const QString userName){
    // data1 *currentUser = nullptr;
    for (const auto& user : usersVector) {
        if (user->getUsername() == userName) {
            // *currentUser = user;
            qDebug() << user->getTheme();
             qDebug() << user->getMode();
            ui->themecombo->setCurrentText(user->getTheme());
            ui->modecombo->setCurrentText(user->getMode());
            break;
        }
    }

    // Update the mode and theme comboboxes based on the selected user
    // if (!currentUser) {

    // }

}

void userDialog::updateusercombo(QString val)
{
    ui->usernamecombo->addItem(val);
}


void userDialog::on_setbtn_clicked()
{
    QString username = ui->usernamecombo->currentText();
    QString theme = ui->themecombo->currentText();
    QString mode = ui->modecombo->currentText();

    std::vector<std::string> selectedSettings;
    selectedSettings.clear();
    selectedSettings.push_back(username.toStdString());
    selectedSettings.push_back(theme.toStdString());
    selectedSettings.push_back(mode.toStdString());
    emit setting(selectedSettings);
}

