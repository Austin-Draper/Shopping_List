#include "widget.h"
#include "workingdatabase.h"
#include <QApplication>
/* TODO
 * 1. version control (git)
 * 2. send text of right side to phone... use free trial of twilio
 * 3. add a toggle feature to highlight right side item to symbolize item has been put in cart
 * (use setfocus at start of onclick when bool flag is set to true then return from onclick function so nothing else happens)
 * need to check if setfocus is already in highlight mode (if it is then that onclick should unhighlight instead by setting nofocus)
 * 4. add feature to place shopping locations into right side
 */
int main(int argc, char *argv[])
{
    //QSqlDatabase db = QSqlDatabase::database();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    workingDatabase slave;
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("Shopping List");
    w.show();

    db = slave.connect_database(db);

    return a.exec();
}
