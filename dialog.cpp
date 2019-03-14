#include "dialog.h"
#include "ui_dialog.h"
#include "workingdatabase.h"
#include "widget.h"
#include "secdialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //connect(ui->dialogCancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->dialogAcceptButton, SIGNAL(clicked()),
            this, SLOT(on_dialogAcceptButton_clicked()), Qt::UniqueConnection);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::SetLabelText (QString &text)
{
    ui->dialog_item_text->setText(text);
}

/*int Dialog::ReturnQuantity()
{
    int _temp = ui->spinBox->value();
    return _temp;
}

double Dialog::ReturnWeight()
{
    double _temp = ui->doubleSpinBox->value();
    return _temp;
}*/

void Dialog::on_dialogAcceptButton_clicked()
{
    qDebug() << "User email is: " << user_name;
    int _quantity = ui->spinBox->value();
    double _weight = ui->doubleSpinBox->value();
    QString _item = ui->dialog_item_text->text();
    //put into right database w/ users email AND put the info onto listWidget2 (right side) properly
    QSqlQuery query;
    query.prepare("SELECT email, rightitem FROM list WHERE email = :email AND rightitem = :rightitem");
    query.bindValue(":email", user_name);
    query.bindValue(":rightitem", _item);
    query.exec();
    if(query.size() == 0)//after the insert, copy and paste code that adds to listWidget2... but set a new class variable (make a getter like before) QString to hold answer
    {//if QString == "", we're done. else, print QString onto right side and set QString to "" again (this portion will be done in widget.cpp upon return from this section
        query.prepare("INSERT INTO list (email, rightitem, quantity, weight) "
                      "VALUES (:email, :rightitem, :quantity, :weight)");
        query.bindValue(":email", user_name);
        query.bindValue(":rightitem", _item);
        query.bindValue(":quantity", _quantity);
        query.bindValue(":weight", _weight);
        query.exec();
        accept();
        return;
    }
    QMessageBox msgBox1;
    msgBox1.setText("This item is already in your list!");
    msgBox1.exec();
    reject();
}

void Dialog::on_dialogDeleteButton_clicked()
{
    bool change;
    QString _item = ui->dialog_item_text->text();
    secDialog _dialog;
    _dialog.SetSecName(user_name);
    _dialog.SetSecItem(_item);
    _dialog.setModal(true);
    auto mybool = _dialog.exec();
    change = mybool;
    SetBool(change);
    reject();
}

void Dialog::on_dialogCancelButton_clicked()
{
    //close();
    //accept();
    reject();
}
