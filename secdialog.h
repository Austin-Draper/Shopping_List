#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>

namespace Ui {
class secDialog;
}

class secDialog : public QDialog
{
    Q_OBJECT

public:
    explicit secDialog(QWidget *parent = nullptr);
    ~secDialog();
    QString sec_user_name;
    QString sec_item;
    void SetSecName(QString &name){sec_user_name = name;}
    void SetSecItem(QString &item){sec_item = item;}

private slots:
    void on_secYes_clicked();

    void on_secNo_clicked();

private:
    Ui::secDialog *ui;
};

#endif // SECDIALOG_H
