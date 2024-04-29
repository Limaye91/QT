#include "serviceconnection.h"

serviceConnection::serviceConnection():dbInstance(databaseConnection::instance())
{
    // setEnginehrs();
    // setTotalkm();
}

serviceConnection::~serviceConnection()
{
    delete dbInstance;
}

int serviceConnection::getEnginehrs()
{
    return dbInstance->getEnginerhrs1();
}

int serviceConnection::getTotalkm()
{
    return dbInstance->getTotalkm1();
}

bool serviceConnection::setusername(const QString &value)
{

    return dbInstance->setnewuser(value);
    //emit newUserAdded(value);

}

void serviceConnection::setusersetting(std::vector<std::string>v)
{
    dbInstance->usersetting(v);
}

data1* serviceConnection::getlastuser()
{
    return dbInstance->lastuserdata();
}

QVector<QString> serviceConnection::getalloperators()
{
    return dbInstance->getAllUsers();
}

QVector<data1*> serviceConnection::getallinserivce()
{
    return dbInstance->getall();
}

// void serviceConnection::setEnginehrs()
// {
//     dbInstance->setEnginerhrs1(40);
//     dbInstance->setEnginerhrs1(20);
// }

// void serviceConnection::setTotalkm()
// {
//     dbInstance->setTotalkm1(10);
// }

void serviceConnection::UpdateKmEngine(int km,int EngineHr,int Fuel){
    qDebug()<<km<<EngineHr;
    dbInstance->setEnginerhrs1(EngineHr);
    dbInstance->setTotalkm1(km);


}

void serviceConnection::resetfucntion()
{
    dbInstance->resetdata();
}
