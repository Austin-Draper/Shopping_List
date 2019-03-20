#include "secdialog.h"
#include "ui_secdialog.h"
#include "workingdatabase.h"
#include "widget.h"
#include "dialog.h"

secDialog::secDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secDialog)
{
    ui->setupUi(this);
    //connect(ui->secNo, SIGNAL(clicked()), this, SLOT(close()));
}

secDialog::~secDialog()
{
    delete ui;
}

void secDialog::SetSecDialogLabelText (QString &text)
{
    ui->secDialogLabel->setText(text);
}
void secDialog::on_secYes_clicked()
{
    QString user_name = sec_user_name;
    QString _item = sec_item;
    QSqlQuery query;
    query.prepare("SELECT email, leftitem FROM profiles WHERE email = :email AND leftitem = :item");
    query.bindValue(":email", user_name);
    query.bindValue(":item", _item);
    query.exec();
    if(query.size() == 0)
    {
        reject();
        return;
    }
    //delete
    query.prepare("DELETE FROM profiles WHERE email = :email AND leftitem = :item");
    query.bindValue(":email", user_name);
    query.bindValue(":item", _item);
    query.exec();
    accept();
    return;
}

 void secDialog::on_secNo_clicked()
 {
     reject();
     return;
 }
