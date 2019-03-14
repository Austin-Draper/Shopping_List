#ifndef RIGHTSECDIALOG_H
#define RIGHTSECDIALOG_H

#include <QDialog>

namespace Ui {
class rightSecDialog;
}

class rightSecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit rightSecDialog(QWidget *parent = nullptr);
    ~rightSecDialog();
    QString right_sec_user_name;
    QString right_sec_item;
    bool dialog_bool = false;
    void SetRightLabelText (QString &text);
    void SetRightSecName(QString &name){right_sec_user_name = name;}
    void SetRightSecItem(QString &item){right_sec_item = item;}
    void SetBool(bool &name){dialog_bool = name;}

private slots:
    void on_rightSecYes_clicked();

    void on_rightSecNo_clicked();

private:
    Ui::rightSecDialog *ui;
};

#endif // RIGHTSECDIALOG_H
