#ifndef FOLD_H
#define FOLD_H
#include <QMainWindow>
#include <QObject>
#include <QMap>
#include <map>
#include <QVector>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

using namespace std;
class fold: public QObject
{
    Q_OBJECT

public:
    explicit fold(QObject *parent = nullptr);
     bool createTable();
    bool addData(const QString& deviceName, const QString& serialName, const QString& assignedTo, const QString& location, const QString& imgPath);
    ~fold();
    // fold();
      QMap<QString , vector <pair <QString,pair<QString , pair<QString , QString>>>>> mp;
    //map<QString, QVector<std::pair<QString, std::pair<QString, std::pair<QString, QString>>>>>ExportData();
      map<QString, QVector<std::pair<QString, std::pair<QString, std::pair<QString, QString>>>>>ExportData();


private:
    QSqlDatabase myDatabase;


public slots:
    void insertData( QVector<QString>&v);
    void removeData(const QString& serialno);
    //void getDatabase();
};

#endif
