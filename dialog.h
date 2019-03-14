#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QString user_name;
    bool dialog_bool = false;
    void SetLabelText (QString &text);
    void SetName(QString &name){user_name = name;}
    void SetBool(bool &name){dialog_bool = name;}
    //int ReturnQuantity();
    //double ReturnWeight();

private slots:
    void on_dialogAcceptButton_clicked();

    void on_dialogDeleteButton_clicked();

    void on_dialogCancelButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
