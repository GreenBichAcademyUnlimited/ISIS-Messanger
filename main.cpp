#include "mainwindow.h"
#include"startsettings.h"
#include"enterwidget.h"
#include"config.h"

#include <QApplication>
#include<QCoreApplication>

#include<QDir>
#include<QDebug>
#include<QFile>
#include<QFileInfo>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    StartSettings settings;
    enterWidget enter;

    QFileInfo finfo(QCoreApplication::applicationFilePath());
    std::string pathF = finfo.absoluteDir().currentPath().toStdString()  + "/"  + CONFIG_PATH + "/config.ini";
    qDebug() << pathF.c_str();
    QFile Config( pathF.c_str() );

    if( ! Config.open( QIODevice::ReadOnly | QIODevice::Text ) ){
        settings.show();
        QObject::connect(&settings, SIGNAL(Registered(bool)), &w, SLOT(setActiv(void)));
    }else{
        QObject::connect(&enter, SIGNAL(PassCorrect()), &w, SLOT(setActiv(void)));
        QObject::connect(&enter, SIGNAL(NewAccount()), &settings, SLOT(setActiv(void)));
    }
    return a.exec();
}
