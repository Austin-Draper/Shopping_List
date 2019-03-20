#ifndef WORKINGDATABASE_H
#define WORKINGDATABASE_H
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <vector>
#include <iostream>
#include <QCryptographicHash>

class workingDatabase
{
private:
public:
    workingDatabase();
    QSqlDatabase connect_database(QSqlDatabase);
    bool check_user(QString, QString);
    bool register_user(QString, QString, QString, QString);
    bool unregister_user(QString, QString);
    bool add_item(QString, QString);
    void setup_home_ui(QString, QVector<QString> &, QVector<QString> &);
    QString user_name;
    void Set_User_Name(QString &name){user_name = name;}

};

#endif // WORKINGDATABASE_H
