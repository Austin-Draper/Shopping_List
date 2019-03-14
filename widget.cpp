#include "widget.h"
#include "ui_widget.h"
#include "workingdatabase.h"
#include "dialog.h"
#include "secdialog.h"
#include "rightsecdialog.h"
#include "rightdeletedialog.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(onlistWidgetItemClicked(QListWidgetItem*)));
    connect(ui->listWidget_2, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(onlistWidget_2ItemClicked(QListWidgetItem*)));
}

Widget::~Widget()
{
    delete ui;
}
void Widget::onlistWidgetItemClicked(QListWidgetItem* item)
{
    //qDebug() << ui->listWidget->currentItem()->text();
    qDebug() << item->text();
    QString _temp = item->text();
    QString final;
    Dialog _dialog;
    _dialog.SetLabelText(_temp);
    _dialog.SetName(test_email);
    _dialog.setModal(true);
    //_dialog.exec();
    auto _answer = _dialog.exec();
    qDebug() << _answer;
    qDebug() << _dialog.dialog_bool;
    //return;
    QSqlQuery query;//error starts here. make it not do this if im coming back from a delete
    if(_dialog.dialog_bool)
    {//remove specific item from left side
        qDebug() << "got here!";
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
        bool _temp = false;
        _dialog.SetBool(_temp);
    }
    if(_answer == 1)
    {
        query.prepare("SELECT rightitem, quantity, weight FROM list WHERE email = :email AND rightitem = :rightitem");
        query.bindValue(":email", test_email);
        query.bindValue(":rightitem", _temp);
        query.exec();
        if(query.size() == 0)
        {
            return;
        }
        while (query.next()){
            QString _rightitem = query.value(0).toString();
            QString _quantity = query.value(1).toString();
            QString _weight = query.value(2).toString();
            if(_quantity == "0" && _weight == "0")
            {
                final = _rightitem;
                ui->listWidget_2->addItem(final);
                return;
            }
            else if(_quantity == "0")
            {
                final = _rightitem + " " + _weight + "lbs";
                ui->listWidget_2->addItem(final);
                return;
            }
            else if(_weight == "0")
            {
                final = _rightitem + " x" + _quantity;
                ui->listWidget_2->addItem(final);
                return;
            }
            else
            {
                final = _rightitem + " x" + _quantity + "  " + _weight + "lbs";
                ui->listWidget_2->addItem(final);
                return;
            }
        }

    }

}

void Widget::onlistWidget_2ItemClicked(QListWidgetItem* item)
{
    //qDebug() << ui->listWidget->currentItem()->text();
    qDebug() << item->text();
    QString _temp = item->text();
    QString _parse = "";
    QString final;
    rightSecDialog _dialog;
    //put text of item into QString and parse it for item without weight or quantity
    //idea: parse left to right until there is a space. that is the item we need
    for(int i = 0; i < _temp.length(); i++)
    {
        if(_temp[i] == " ")//if white space found, stop for loop
        {
            break;
        }
        else
        {
            _parse = _parse + _temp[i];
        }
    }//_parse now holds just the items name


    _dialog.SetRightLabelText(_temp);
    _dialog.SetRightSecName(test_email);
    _dialog.SetRightSecItem(_parse);
    _dialog.setModal(true);
    //_dialog.exec();
    auto _answer = _dialog.exec();
    qDebug() << _answer;
    //return;
    QSqlQuery query;//error starts here. make it not do this if im coming back from a delete
    if(_answer == 1)//verify 1 means true and 0 means false
    {//remove specific item from right side
        qDebug() << "got here!";
        delete ui->listWidget_2->takeItem(ui->listWidget_2->row(item));
        bool _temp = false;
        _dialog.SetBool(_temp);
    }
}

void Widget::on_loginSubmit_clicked()//after left_vector for loop, do the EXACT same 1 line loop but for right_vector instead and added to listWidget2
{
    QVector<QString> left_vector, right_vector;
    QString _email = ui->emailLineEdit->text();
    QString _password = ui->passwordLineEdit->text();
    bool logincheck = false;
    workingDatabase slave1;
    logincheck = slave1.check_user(_email, _password);
    if(logincheck)
    {
        ui->stackedWidget->setCurrentIndex(1);//navigates to homepage
        ui->welcomeLabel->setText("Welcome " + slave1.user_name);//_email
        slave1.setup_home_ui(_email, left_vector, right_vector);
        test_email = _email;
        for(int i = 0; i < left_vector.size(); i++)
        {
            ui->listWidget->addItem(left_vector.at(i));
        }
        QVector<QString>().swap(left_vector);

        for(int j = 0; j < right_vector.size(); j++)
        {
            ui->listWidget_2->addItem(right_vector.at(j));
        }
        QVector<QString>().swap(right_vector);
    }
}

void Widget::on_registerButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);//navigates to register page
}

void Widget::on_regBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);//navigates to login page
}

void Widget::on_regRegisterButton_clicked()
{
    bool registered = false;
    workingDatabase slave2;
    QString _email = ui->regEmailLineEdit->text();
    QString _username = ui->regUsernameLineEdit->text();
    QString _password = ui->regPasswordLineEdit->text();
    QString _phone = ui->regPhoneLineEdit->text();
    registered = slave2.register_user(_email, _username, _password, _phone);
    if(registered)
    {
        QMessageBox msgBox1;
        msgBox1.setText("You have been Registered!");
        msgBox1.exec();
        ui->stackedWidget->setCurrentIndex(0);
        return;
    }

    QMessageBox msgBox2;
    msgBox2.setText("User Already Exists!");
    msgBox2.exec();
}

void Widget::on_unregisterButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Widget::on_unregisterBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_unregisterUnregisterButton_clicked()
{
    bool unregistered = false;
    workingDatabase slave3;
    QString _email = ui->unregisterEmailLineEdit->text();
    QString _password = ui->unregisterPasswordLineEdit->text();
    unregistered = slave3.unregister_user(_email, _password);
    if(unregistered)
    {
        QMessageBox msgBox1;
        msgBox1.setText("You have been Unregistered!");
        msgBox1.exec();
        ui->stackedWidget->setCurrentIndex(0);
        return;
    }

    QMessageBox msgBox2;
    msgBox2.setText("Failed to Unregister!");
    msgBox2.exec();
}

void Widget::on_homeLogout_clicked()
{
    ui->listWidget->clear();
    ui->stackedWidget->setCurrentIndex(0);

}

void Widget::on_homeAddButton_clicked()
{
    //same as above stuff but bool for if put into left array or not. if not (bool is false), that means their attempted add is a duplicate
    bool duplicate = true;
    workingDatabase slave4;//BREAKING CODE
    QString _item = ui->homeAddItemLineEdit->text();
    duplicate = slave4.add_item(_item, test_email);
    if(duplicate)
    {
        QMessageBox msgBox1;
        msgBox1.setText("This item is already in your list!");
        msgBox1.exec();
        return;
    }
    //if not duplicate... put into leftitem (already done) AND put sorted on left side
    qDebug() << "Not a duplicate... will add to UI list now";
    ui->listWidget->addItem(_item);
}

void Widget::on_homeClearButton_clicked()
{
    rightdeletedialog _dialog;
    //QString _temp = "Are you sure you want to delete your shopping list?";
    _dialog.SetRightDeleteName(test_email);
    _dialog.setModal(true);
    auto _answer = _dialog.exec();
    //if _answer == 1 (true), call ui->listwidget2->clear(); otherwise... do nothing (no need for an else statement since there is nothing after if statement anyway)
    if(_answer == 1)
    {
        ui->listWidget_2->clear();
        _answer = 0;
    }
}
