#include "fold.h"
#include <QSettings>
#include <QSqlDatabase>
#include <QMessageBox>
using namespace std;
fold::fold(QObject *parent) : QObject(parent)
{
    myDatabase = QSqlDatabase::addDatabase("QSQLITE");
    myDatabase.setDatabaseName("myDatabase.db");

    if(myDatabase.open()){

        qDebug() << "Connection Successful.";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
    createTable();
}

fold::~fold()
{
    if (myDatabase.isOpen())
    {
        myDatabase.close();
    }
}


bool fold::createTable()
{
    bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS DeviceTracker("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "devicename TEXT, "
                  "serialno TEXT, "
                  "assignedto TEXT, "
                  "location TEXT, "
                  "imgpath TEXT"
                  ");");


    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'people': one might already exist.";
        success = false;
    }

    return success;
}



//inserting data into table
bool fold::addData(const QString& deviceName, const QString& serialName, const QString& assignedTo, const QString& location, const QString& imgPath)
{
    qDebug() <<"Data : "<<deviceName<<serialName<< assignedTo<<location<<imgPath;
    bool success = false;

    if (!deviceName.isEmpty())
    {
        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO DeviceTracker(devicename, serialno, assignedto, location, imgpath)"
                         "VALUES (:deviceName, :serialName, :assignedTo, :location, :imgPath)");

        queryAdd.bindValue(":deviceName", deviceName);
        queryAdd.bindValue(":serialName", serialName);
        queryAdd.bindValue(":assignedTo", assignedTo);
        queryAdd.bindValue(":location", location);
        queryAdd.bindValue(":imgPath", imgPath);

        if (queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add data failed: " << queryAdd.lastError().text();
        }

    }
    else
    {
        qDebug() << "add data failed: name cannot be empty";
    }

    return success;
}














void fold::insertData( QVector<QString> &v)
{
    mp[v[0]].push_back({v[1],{v[2],{v[3],v[4]}}});
    for(auto it : mp[v[0]])
    {
        qDebug() << it;
    }

    // Assuming mp is your QMap structure
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        const QString& deviceName = it.key(); // deviceName is the key
        const auto& values = it.value();
        for (const auto& value : values) {
            const QString& serialName = value.first;
            const QString& assignedTo = value.second.first;
            const QString& location = value.second.second.first;
            const QString& imgPath = value.second.second.second;

            bool success = addData(deviceName, serialName, assignedTo, location, imgPath);
            if (!success) {
                qDebug() << "Failed to add data for entry:" << deviceName << serialName << assignedTo << location << imgPath;
                // Handle failure if needed
            }
        }
    }






}


void fold::removeData(const QString& serialno)
{
    bool success = false;

    QSqlQuery query;
    query.prepare("SELECT * FROM DeviceTracker WHERE serialno = (:serialno)");
    query.bindValue(":serialno", serialno);
    if (query.exec() && query.next()) {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM DeviceTracker WHERE serialno = (:serialno)");
        queryDelete.bindValue(":serialno", serialno);
        success = queryDelete.exec();
        if(!success) {
            qDebug() << "remove person failed: " << queryDelete.lastError();
        }
    } else {
        QMessageBox::warning(nullptr, "Error", "Remove serial number failed: doesn't exist");
    }


}

map<QString, QVector<std::pair<QString, std::pair<QString, std::pair<QString, QString>>>>>fold::ExportData()


{
    map<QString, QVector<std::pair<QString, std::pair<QString, std::pair<QString, QString>>>>> mp2;

    QSqlQuery exportQuery;
    exportQuery.prepare("SELECT * FROM DeviceTracker;");
    if (!exportQuery.exec()) {
        qDebug() << "Error executing query:" << exportQuery.lastError().text();
        return mp2; // Return empty map on error
    }

    while (exportQuery.next())
    {
        QString key = exportQuery.value(1).toString();  // Assuming the first column is the key
        // Store data from each column in the vector
        QString col1 = exportQuery.value(2).toString();  // Assuming the second column
        QString col2 = exportQuery.value(3).toString();  // Assuming the third column
        QString col3 = exportQuery.value(4).toString();  // Assuming the fourth column
        QString col4 = exportQuery.value(5).toString();  // Assuming the fifth column

        // Construct the nested data structure and insert into map
        mp2[key].push_back({ col1, { col2, { col3, col4 } } });
    }
    qDebug()<<"hiee";
    return mp2;
}


