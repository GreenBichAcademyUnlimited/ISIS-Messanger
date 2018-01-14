#include "widget.h"
#include <QApplication>
#include"mydb.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mydb * db = new mydb();
    Widget w;
    w.show();
    return a.exec();
}
