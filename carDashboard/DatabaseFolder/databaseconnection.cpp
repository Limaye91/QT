#include "databaseconnection.h"
#include <QSettings>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QTimer>
databaseConnection::databaseConnection()
{
    carDatabase = QSqlDatabase::addDatabase("QSQLITE");
    carDatabase.setDatabaseName("carDatabase.db");

    if(carDatabase.open()){

        qDebug() << "Connection Successful.";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
    createTable();
    // QTimer* timer=new QTimer(this);
    // connect(timer, &QTimer::timeout, this, [this]() {
    //     setTotalkm1(20);
    //     setEnginerhrs1(1);
    // });
    // timer->start(1000);


}
// databaseConnection* databaseConnection::_instance = nullptr;
// bool databaseConnection::instanceInitialized = false;

bool databaseConnection::createTable()
{
    bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS UserPreference ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "username TEXT UNIQUE, "
                  "theme TEXT, "
                  "mode TEXT, "
                  "individualkm DECIMAL(10,2)"
                  ");");

    if (!query.exec()) {
        qDebug() << "Error creating UserPreference table:" << query.lastError().text();
        qDebug() << "Query: " << query.lastQuery();
    } else {
        qDebug() << "UserPreference table created successfully.";
    }

    query.prepare("CREATE TABLE IF NOT EXISTS CarDashboard("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "username TEXT,"
                  "enginehours DECIMAL(10,2), "
                  "Fuellevel INTEGER,"
                  "totalkilometers DECIMAL(10,2),"
                  "FOREIGN KEY (username) REFERENCES UserPreference (username)"
                  ")");
    if (!query.exec()) {
        qDebug() << "Error creating CarDashboard table:" << query.lastError().text();
        success = false;
    } else {
        qDebug() << "CarDashboard table created successfully.";
        success = true;
    }
    //creating table for user preference


    // creating table for vehicle status

    return success;
}

databaseConnection::~databaseConnection()
{
    if (carDatabase.isOpen())
    {
        carDatabase.close();
    }
}

bool databaseConnection::setEnginerhrs1(int val)
{
 {
        // Assuming you have a QSqlDatabase object named 'db' already created and connected
        QSqlDatabase::database().transaction();
        QSqlQuery query;

        // Get the current engine hours from the database
        query.prepare("SELECT enginehours FROM CarDashboard ORDER BY id DESC LIMIT 1");
        if (!query.exec()) {
            qDebug() << "Error retrieving engine hours:" << query.lastError().text();
            return false;
        }

        double currentEngineHours = 0.0;
        if (query.next()) {
            currentEngineHours = query.value(0).toDouble();
        }

        // Calculate the new engine hours by adding the value 'val'
        double newEngineHours = currentEngineHours + val;

        // Update the previous row in the database with the new engine hours
        query.prepare("UPDATE CarDashboard SET enginehours = :newEngineHours WHERE id = (SELECT id FROM CarDashboard ORDER BY id DESC LIMIT 1)");
        query.bindValue(":newEngineHours", newEngineHours);
        if (!query.exec()) {
            qDebug() << "Error updating engine hours:" << query.lastError().text();
            QSqlDatabase::database().rollback();
            return false;
        }
        QSqlDatabase::database().commit();
        qDebug() << "Engine hours updated successfully";
        return true;
    }

}

bool databaseConnection::setTotalkm1(int val2)
{
        QSqlDatabase::database().transaction();
        // Assuming you have a QSqlDatabase object named 'db' already created and connected

        QString UpdateTotalKm="SELECT totalkilometers FROM CarDashboard ORDER BY id DESC LIMIT 1";
        QSqlQuery query;

        // Get the current engine hours from the database
        query.prepare(UpdateTotalKm);
        if (!query.exec()) {
            qDebug() << "Error retrieving engine hours:" << query.lastError().text();
            return false;
        }

        double currenttotalkilometers = 0;
        if (query.next()) {
            qDebug()<<query.value(0).toDouble();
            currenttotalkilometers = query.value(0).toDouble();
        }

        // Calculate the new engine hours by adding the value 'val'
        double newtotalkilometers= currenttotalkilometers+ val2;

        // Update the previous row in the database with the new engine hours
        query.prepare("UPDATE CarDashboard SET totalkilometers = :newtotalkilometers WHERE id = (SELECT id FROM CarDashboard ORDER BY id DESC LIMIT 1)");
        query.bindValue(":newtotalkilometers", newtotalkilometers);
        if (!query.exec()) {
            qDebug() << "Error updating km hours:" << query.lastError().text();
            QSqlDatabase::database().rollback();
            return false;
        }
        QSqlDatabase::database().commit();
        qDebug() << "km hours updated successfully";
        return true;

    // Increment Total_KM in CarInfo table
    // QSqlDatabase::database().transaction();
    // QString UpdateTotalKm="SELECT totalkilometers FROM CarDashboard ORDER BY id DESC LIMIT 1";
    // QSqlQuery updateCarInfoQuery;
    // updateCarInfoQuery.prepare(UpdateTotalKm);
    // updateCarInfoQuery.bindValue(":val2", val2);
    // qDebug()<<updateCarInfoQuery.exec();
    // if (!updateCarInfoQuery.exec()) {
    //     qDebug() << "Error incrementing Total_KM value in CarDashboard: " << updateCarInfoQuery.lastError().text();
    //     QSqlDatabase::database().rollback(); // Rollback transaction in case of error
    //     return false;
    // }
    // qDebug() << "km hours updated successfully";
    // QSqlDatabase::database().commit();
    // return true;
}


int databaseConnection::getTotalkm1() {
    QString selectQuery = "SELECT totalkilometers FROM CarDashboard LIMIT 1";
    QSqlQuery query(selectQuery);
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    } else {
        qDebug() << "Error retrieving Total_KM value: " << query.lastError().text();
        return -1; // Return an error code or handle the error as required
    }
}

bool databaseConnection::setnewuser(const QString &newuser)
{
    {
        // Prepare the SQL query to insert a new user
        QSqlQuery query;
        query.prepare("INSERT INTO UserPreference (username) VALUES (:username)");
        query.bindValue(":username", newuser);

        // Execute the query
        if (!query.exec()) {
            qDebug() << "Error executing query:" << query.lastError().text();
            return false;
        }

        qDebug() << "New user inserted successfully";
        return true;
    }

}

bool databaseConnection::usersetting(std::vector<std::string>values)
{
    if (values.size() != 3) {
        qDebug() << "Error: Incorrect number of values provided.";
        return false;
    }

    const std::string& username = values[0];
    const std::string& theme = values[1];
    const std::string& mode = values[2];

    QSqlQuery query(carDatabase);
    query.prepare("UPDATE UserPreference SET theme = :theme, mode = :mode WHERE username = :username");
    query.bindValue(":theme", QString::fromStdString(theme));
    query.bindValue(":mode", QString::fromStdString(mode));
    query.bindValue(":username", QString::fromStdString(username));

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    qDebug() << "Preferences updated successfully for username:" << QString::fromStdString(username);

    // Update CarDashboard table (assuming carDatabase is a valid QSqlDatabase)
    QSqlQuery updateCarInfoQuery(carDatabase);
    updateCarInfoQuery.prepare("UPDATE CarDashboard SET username = :username WHERE username != :username");
    updateCarInfoQuery.bindValue(":username", QString::fromStdString(username));

    if (!updateCarInfoQuery.exec()) {
        qDebug() << "Error updating CarInfo: " << updateCarInfoQuery.lastError().text();
        return false;
    }

    return true;
}

void databaseConnection::resetdata()
{
    QString resetcardashbaord="UPDATE CarDashboard SET totalkilometers=0, enginehours=0";
    QSqlQuery carquery;
    if(!carquery.exec(resetcardashbaord))
    {
        qDebug()<<"error in reseting"<<carquery.lastError().text();
        return;
    }
    qDebug()<<"reset fucntion successful";
}


int databaseConnection::getEnginerhrs1() {
    QString selectQuery = "SELECT enginehours FROM CarDashboard LIMIT 1";
    QSqlQuery query(selectQuery);
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    } else {
        qDebug() << "Error retrieving Total_KM value: " << query.lastError().text();
        return -1; // Return an error code or handle the error as required
    }
}

data1* databaseConnection::lastuserdata() {
    // Connect to the database and perform the necessary setup

    // Query to fetch the latest entry from the CarDashboard table
    QSqlQuery carQuery("SELECT * FROM CarDashboard ORDER BY id DESC LIMIT 1");
    if (carQuery.exec()) {
        if (carQuery.next()) {
            // Populate the Data object with data from the CarDashboard table
            data1* lastuser = new data1();
            lastuser->setUsername(carQuery.value("username").toString());
            lastuser->setEngineHours(carQuery.value("enginehours").toDouble());
            lastuser->setFuelLevel(carQuery.value("Fuellevel").toInt());
            lastuser->setTotalKilometers(carQuery.value("totalkilometers").toDouble());

            // Fetch related entries from the UserPreference table using the username
            QString username = carQuery.value("username").toString();
            QSqlQuery userQuery;
            userQuery.prepare("SELECT * FROM UserPreference WHERE username = :username");
            userQuery.bindValue(":username", username);
            if (userQuery.exec()) {
                if (userQuery.next()) {
                    // Populate the Data object with data from the UserPreference table
                    lastuser->setTheme(userQuery.value("theme").toString());
                    lastuser->setMode(userQuery.value("mode").toString());
                    lastuser->setIndividualKm(userQuery.value("individualkm").toDouble());

                    // Return the Data object
                    return lastuser;
                } else {
                    qDebug() << "No matching entry found in UserPreference table.";
                }
            } else {
                qDebug() << "Error executing UserPreference query:" << userQuery.lastError().text();
            }
        } else {
            qDebug() << "No entries found in CarDashboard table.";
        }
    } else {
        qDebug() << "Error executing CarDashboard query:" << carQuery.lastError().text();
    }

    // Close the database connection and perform cleanup

    // Return nullptr if data retrieval failed
    return nullptr;
}


// std::vector<data*> data::LoadAllUserData() {
//     std::vector<data*> userDataList;

//     QString selectAllUserDataQuery = "SELECT * FROM UserPrefrence";
//     QSqlQuery allUserDataQuery(selectAllUserDataQuery);
//     while (allUserDataQuery.next()) {
//         data* userdata = new data();

//         // Retrieve data from the query result
//         userdata->setTheme(userQuery.value("theme").toString());
//         userdata->setMode(userQuery.value("mode").toString());
//         userdata->setIndividualKm(userQuery.value("individualkm").toDouble());

//     // Add the userData to userDataList
//         userDataList.push_back(userdata);
//     }

//     return userDataList;
// }

QVector<QString> databaseConnection::getAllUsers() {
    QVector<QString> users;

    // Assuming you have a QSqlDatabase instance named db
    if (carDatabase.isOpen()) {
        QSqlQuery query(carDatabase);
        if (query.exec("SELECT username FROM UserPreference")) {
            while (query.next()) {
                QString username = query.value(0).toString();
                users.push_back(username);
            }
        } else {
            qDebug() << "Error executing query:" << query.lastError().text();
        }
    } else {
        qDebug() << "Database is not open.";
    }

    return users;
}


QVector<data1* > databaseConnection::getall()
{
    QVector<data1*> userDataList1;

        QString selectAllUserDataQuery = "SELECT * FROM UserPreference";
        QSqlQuery allUserDataQuery(selectAllUserDataQuery);
        while (allUserDataQuery.next()) {
            data1* userdata = new data1();

            // Retrieve data from the query result
            userdata->setUsername((allUserDataQuery.value("username").toString()));
            userdata->setMode(allUserDataQuery.value("mode").toString());
            userdata->setTheme(allUserDataQuery.value("theme").toString());
            // userdata->setIndividualKm(allUserDataQuery.value("individualkm").toDouble());

        // Add the userData to userDataList
            userDataList1.push_back(userdata);
        }

        for (const auto& detail : userDataList1) {
            qDebug()<<detail->getUsername()<<detail->getMode()<<detail->getTheme();
        }
        return userDataList1;
}
