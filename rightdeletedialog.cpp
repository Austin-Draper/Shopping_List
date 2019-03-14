#include "rightdeletedialog.h"
#include "ui_rightdeletedialog.h"
#include "workingdatabase.h"

rightdeletedialog::rightdeletedialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rightdeletedialog)
{
    ui->setupUi(this);
}

rightdeletedialog::~rightdeletedialog()
{
    delete ui;
}

void rightdeletedialog::on_rightDeleteYes_clicked()
{
    QString user_name = right_delete_user_name;
    qDebug() << right_delete_user_name;
    QSqlQuery query;
    //delete
    query.prepare("DELETE * FROM list WHERE email = :email");
    query.bindValue(":email", user_name);
    query.exec();
    accept();
    return;

}

void rightdeletedialog::on_rightDeleteNo_clicked()
{
    reject();
    return;

}
