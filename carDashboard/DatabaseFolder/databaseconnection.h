
#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMainWindow>
#include "../data/data1.h"
class databaseConnection: public QObject
{

    Q_OBJECT
public:
    data1* lastuserdata();
    QVector<QString> getAllUsers();
    QVector<data1*> getall();
    bool createTable();
    ~databaseConnection();

    static databaseConnection* instance()
    {
        static databaseConnection* _instance;
        if(!_instance)
            _instance= new databaseConnection();
        return _instance;
    }


    // static databaseConnection& getInstance() {
    //     // Check if instance is initialized
    //     if (!instanceInitialized) {
    //         instance = new Singleton();
    //         instanceInitialized = true;
    //     }
    //     return *instance;
    // }







    bool setEnginerhrs1(int val1);
    bool setTotalkm1(int val2);
    int getEnginerhrs1();
    int getTotalkm1();
    bool setnewuser(const QString&);
    bool usersetting(std::vector<std::string>);

    void resetdata();

private:

    //static bool instanceInitialized;

    // databaseConnection* databaseConnection::_instance = nullptr;
    // bool databaseConnection::instanceInitialized = false;

     databaseConnection();
    databaseConnection(databaseConnection& other)=delete;
     databaseConnection& operator= (databaseConnection& other)=delete;
    QSqlDatabase carDatabase;
};

#endif // DATABASECONNECTION_H
