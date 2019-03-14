#include "workingdatabase.h"
#include "widget.h"
#include "ui_widget.h"

workingDatabase::workingDatabase()
{
    qDebug() << "constructor!";
}

QSqlDatabase workingDatabase::connect_database(QSqlDatabase db)
{

    //QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("Griff");
    db.setPassword("Guntherpotato5000!");
    db.setDatabaseName("shopping_list");
    if(db.open()){
        //attempt a query
        //QSqlQuery query;
        //query.exec("SELECT email FROM users WHERE email = 'austin.draper@aol.com'");
        //while (query.next()){
            //QString email = query.value(0).toString();
            //qDebug() << email << endl;
        //}

        qDebug("database opened!!!!");
        return db;
    }
    qDebug("database didn't open!!!!");
    return db;
}

bool workingDatabase::check_user(QString _email, QString _password)
{
    //this will call a function if user found to go to home page and display their info

    QSqlQuery query;
    query.prepare("SELECT email, password, username FROM users WHERE email = :email AND password = :password");
    query.bindValue(":email", _email);
    query.bindValue(":password", _password);
    query.exec();

     while (query.next()){
         QString email = query.value(0).toString();
         QString password = query.value(1).toString();
         QString _username = query.value(2).toString();
         if(email == _email && password == _password)
         {
            //go to homepage
             Set_User_Name(_username);
             return true;
         }
            }
    qDebug() << "User or Password Incorrect or not Registered" << endl;
    return false;
}

bool workingDatabase::register_user(QString _email, QString _username, QString _password, QString _phone)
{
    //TODO: make a popup that says whether registration was successful or not. go to login page if success, stay on page if not successful
    QSqlQuery query;
    query.prepare("SELECT email, password FROM users WHERE email = :email AND password = :password");
    query.bindValue(":email", _email);
    query.bindValue(":password", _password);
    query.exec();
    if(query.size() == 0)
    {
        query.prepare("INSERT INTO users (email, username, password, phone_number) "
                      "VALUES (:email, :user, :pass, :phone)");
        query.bindValue(":email", _email);
        query.bindValue(":user", _username);
        query.bindValue(":pass", _password);
        query.bindValue(":phone", _phone);
        query.exec();
        qDebug() << "User has been Registered!";
        return true;
    }

    qDebug() << "User already exists!";
    return false;
}

bool workingDatabase::unregister_user(QString _email, QString _password)
{
    //TODO: make a popup that says whether registration was successful or not. go to login page if success, stay on page if not successful
    QSqlQuery query;
    query.prepare("SELECT email, password FROM users WHERE email = :email AND password = :password");
    query.bindValue(":email", _email);
    query.bindValue(":password", _password);
    query.exec();
    if(query.size() == 0)
    {
        qDebug() << "User not found!";
        return false;
    }
    query.prepare("DELETE FROM users WHERE email = :email AND password = :pass");
    query.bindValue(":email", _email);
    query.bindValue(":pass", _password);
    query.exec();
    query.prepare("DELETE FROM profiles WHERE email = :email");
    query.bindValue(":email", _email);
    query.exec();
    qDebug() << "User deleted!";
    return true;
}

bool workingDatabase::add_item(QString _item, QString user_email)
{
    QSqlQuery query;
    query.prepare("SELECT email, leftitem FROM profiles WHERE email = :email AND leftitem = :leftitem");
    query.bindValue(":email", user_email);
    query.bindValue(":leftitem", _item);
    query.exec();
    if(query.size() == 0)
    {
        query.prepare("INSERT INTO profiles (email, leftitem) "
                      "VALUES (:email, :leftitem)");
        query.bindValue(":email", user_email);
        query.bindValue(":leftitem", _item);
        query.exec();
        return false;
    }
    return true;


}

void workingDatabase::setup_home_ui(QString _email, QVector<QString> &left_vector, QVector<QString> &right_vector)//add a &right_vector and copy code over to get appropriate strings
{
    QString final = "";
    QSqlQuery query;
    query.prepare("SELECT leftitem FROM profiles WHERE email = :email");
    query.bindValue(":email", _email);
    query.exec();
    while (query.next()){
        QString _item = query.value(0).toString();
        left_vector.push_back(_item);
    }
    query.prepare("SELECT rightitem, quantity, weight FROM list WHERE email = :email");
    query.bindValue(":email", _email);
    query.exec();
    while (query.next()){
        QString _item = query.value(0).toString();


        QString _quantity = query.value(1).toString();
        QString _weight = query.value(2).toString();
        if(_quantity == "0" && _weight == "0")
        {
            final = _item;
            right_vector.push_back(final);
        }
        else if(_quantity == "0")
        {
            final = _item + " " + _weight + "lbs";
            right_vector.push_back(final);
        }
        else if(_weight == "0")
        {
            final = _item + " x" + _quantity;
            right_vector.push_back(final);
        }
        else
        {
            final = _item + " x" + _quantity + "  " + _weight + "lbs";
            right_vector.push_back(final);
        }

    }

}
