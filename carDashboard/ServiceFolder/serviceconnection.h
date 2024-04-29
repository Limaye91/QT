    #ifndef SERVICECONNECTION_H
#define SERVICECONNECTION_H

#include <QObject>

#include "../DatabaseFolder/databaseconnection.h"

class serviceConnection :public QObject
{
    Q_OBJECT

private:
    databaseConnection *dbInstance;
// signals:
//     void newUserAdded(QString);
public:

    serviceConnection();
    ~serviceConnection();

    // void setEnginehrs();
    // void setTotalkm();
    int getEnginehrs();
    int getTotalkm();

    bool setusername(const QString &value);
    void setusersetting(std::vector<std::string>);
    data1* getlastuser();
    QVector<QString> getalloperators();
    QVector<data1*> getallinserivce();

    void UpdateKmEngine(int km,int EngineHr,int Fuel);
    void resetfucntion();

};

#endif // SERVICECONNECTION_H
