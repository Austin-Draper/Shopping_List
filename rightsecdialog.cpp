#include "rightsecdialog.h"
#include "ui_rightsecdialog.h"
#include "workingdatabase.h"

rightSecDialog::rightSecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rightSecDialog)
{
    ui->setupUi(this);
}

rightSecDialog::~rightSecDialog()
{
    delete ui;
}

void rightSecDialog::SetRightLabelText (QString &text)
{
    ui->rightSecDialogLabel->setText(text);
}

void rightSecDialog::on_rightSecYes_clicked()
{
    QString user_name = right_sec_user_name;
    QString _item = right_sec_item;
    qDebug() << right_sec_user_name;
    qDebug() << right_sec_item;
    QSqlQuery query;
    query.prepare("SELECT email, rightitem FROM list WHERE email = :email AND rightitem = :item");
    query.bindValue(":email", user_name);
    query.bindValue(":item", _item);
    query.exec();
    if(query.size() == 0)
    {
        reject();
        return;
    }
    //delete
    query.prepare("DELETE FROM list WHERE email = :email AND rightitem = :item");
    query.bindValue(":email", user_name);
    query.bindValue(":item", _item);
    query.exec();
    accept();
    return;
}

void rightSecDialog::on_rightSecNo_clicked()
{
    reject();
    return;
}
