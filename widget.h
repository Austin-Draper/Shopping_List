#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    QString test_email;
    bool _result;
    void SetName(QString &name){test_email = name;}
    void GetResult(bool &answer){_result = answer;}

private slots:
    void on_loginSubmit_clicked();

    void on_registerButton_clicked();

    void on_regBackButton_clicked();

    void on_regRegisterButton_clicked();

    void on_unregisterButton_clicked();

    void on_unregisterBackButton_clicked();

    void on_unregisterUnregisterButton_clicked();

    void on_homeLogout_clicked();

    void on_homeAddButton_clicked();

    void onlistWidgetItemClicked(QListWidgetItem* item);

    void onlistWidget_2ItemClicked(QListWidgetItem* item);

    void on_homeClearButton_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
