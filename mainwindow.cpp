#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"config.h"
#include"sam.h"

#include<QDesktopWidget>
#include<QMessageBox>
#include<QFileInfo>
#include<QDir>
//#include<QDebug>

void MainWindow::initMenu(void){
    Friends = new QMenu(this);
    Advance = new QMenu(this);
    Settings = new QMenu(this);

    //friends
    Friends_add = new QAction(this);
    Friends_add->setShortcut(QKeySequence(tr("Ctrl+A")));
    Friends_add->setText(tr("&Add Friend"));

    Friends = menuBar()->addMenu(tr("&Friends"));
    Friends->addAction(Friends_add);

    //


    // Settings
    Settings = menuBar()->addMenu(tr("Settings"));
    Settings_Network = new QAction(this);
    Settings_Network->setText(tr("Network Settings"));


    Settings->addAction(Settings_Network);


    //advance
    Advance_Exit = new QAction(this);
    Advance_About = new QAction(this);

    Advance_Exit->setShortcut(QKeySequence(tr("Ctrl+F4")));
    Advance_Exit->setStatusTip( tr("&Exit from program") );
    Advance_Exit->setText( tr("&Exit") );

    Advance_About->setShortcut(QKeySequence(tr("F1")));
    Advance_About->setStatusTip(tr("&About of program"));
    Advance_About->setText(tr("&About"));




    Advance = menuBar()->addMenu(tr("Advance"));

    //
    Advance->addAction(Advance_About);
    Advance->addSeparator();
    Advance->addAction(Advance_Exit);


//connects

//Advance
     connect(Advance_Exit,SIGNAL(triggered(bool)),this,SLOT(close()));
     QMessageBox * advBox = new QMessageBox(this);
     advBox->setText(tr("ISIS-Mess(e)anger 2018-?"));
     connect(Advance_About,SIGNAL(triggered(bool)),advBox,SLOT(exec()));
//Settings



}

void MainWindow::setActiv(){
    this->show();
    QFileInfo finfo(QCoreApplication::applicationFilePath());
    std::string pathF = finfo.absoluteDir().currentPath().toStdString() + "/" + CONFIG_PATH;

    config = new QSettings((pathF+"/config.ini").c_str(), QSettings::NativeFormat);
    if(config->value("SAM/Privkey",0) == 0){
        if(config->value("SAM/host",0) == 0 || config->value("SAM/port",0) == 0){
            QMessageBox error;
            error.setText(tr("Please create new account...(config)"));
            error.exec();
            this->setEnabled(false);
        }
         while(1){
             sam Client(config->value("SAM/host").toString().toStdString().c_str(),
                        atoi( config->value("SAM/port").toString().toStdString().c_str()));
             Client.generateDestination();

             if(!Client.getError()){
                 config->setValue("SAM/Privkey",Client.getPrivkey());
                 config->setValue("SAM/Pubkey",Client.getPubkey());
                 break;
             }
             QMessageBox error;
             error.setText(tr("Error with SAM, try new"));
             error.exec();
         }
    }
    //qDebug() << "PASS OF GUY=" << PassOfGuy;

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)

{
    QRect ScreenRect
         = QApplication::desktop()->screenGeometry();

    this->initMenu();
    this->setGeometry(ScreenRect.width()/4,ScreenRect.height()/4,500,500);

}

MainWindow::~MainWindow()
{
    //delete [] config;
}
