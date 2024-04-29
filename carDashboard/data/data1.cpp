#include "data1.h"

data1::data1(QObject * parent): QObject(parent) {}

// QVector<data*> data::getUserDataList() const {
//     return userDataList;
// }

// void data1::pushUserData(data1* userdata) {
//     userDataList.push_back(userdata);
// }

QString data1::getUsername() const
{
    return username;
}


data1::~data1(){}

//setter function definition


void data1::setUsername(const QString &value) {
    username = value;
}

QString data1::getTheme() const
{
    return theme;
}

int data1::getEngineHours()
{
    return enginehours;
}

int data1::getTotalKilometers()
{
    return totalkilometers;
}

int data1::getFuelLevel()
{
    return fuellevel;
}
void data1::setTheme(const QString &value) {
    theme = value;
}

QString data1::getMode() const
{
    return mode;
}

void data1::setMode(const QString &value) {
    mode = value;
}

void data1::setIndividualKm(double value) {
    individualkm = value;
}

void data1::setEngineHours(double value) {
    enginehours = value;
}

void data1::setFuelLevel(int value) {
    fuellevel = value;
}

void data1::setTotalKilometers(double value) {
    totalkilometers = value;
}
