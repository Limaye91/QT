#ifndef DATA1_H
#define DATA1_H
#include<QVector>
#include <QObject>

class data1:public QObject
{
    Q_OBJECT

private:
    QString username;
    QString theme;
    QString mode;
    double individualkm;
    double enginehours;
    int fuellevel;
    double totalkilometers;



public:
    data1(QObject *parent=nullptr);

    // static QVector<data1*> userDataList;

    //all the getter and setter
    // QVector<data1*> getUserDataList() const; // Function to get userDataList

    // Function to push a Data object into userDataList
    void pushUserData(data1 *userdata);


    QString getUsername() const;
    void setUsername(const QString &value);

    QString getTheme() const;
    void setTheme(const QString &value);

    QString getMode() const;
    void setMode(const QString &value);

    double getIndividualKm() const;
    void setIndividualKm(double value);

    int getEngineHours();
    void setEngineHours(double value);

    int getFuelLevel();
    void setFuelLevel(int value);

    int getTotalKilometers();
    void setTotalKilometers(double value);
    ~data1();
};

#endif // DATA1_H
