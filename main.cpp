#include "mainwindow.h"
#include"startsettings.h"
#include <openssl/sha.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    StartSettings settings;
    settings.show();
    //w.show();

    return a.exec();
}
