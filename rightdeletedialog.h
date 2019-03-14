#ifndef RIGHTDELETEDIALOG_H
#define RIGHTDELETEDIALOG_H

#include <QDialog>

namespace Ui {
class rightdeletedialog;
}

class rightdeletedialog : public QDialog
{
    Q_OBJECT

public:
    explicit rightdeletedialog(QWidget *parent = nullptr);
    ~rightdeletedialog();
    QString right_delete_user_name;
    void SetRightDeleteName(QString &name){right_delete_user_name = name;}

private slots:
    void on_rightDeleteYes_clicked();

    void on_rightDeleteNo_clicked();

private:
    Ui::rightdeletedialog *ui;
};

#endif // RIGHTDELETEDIALOG_H
