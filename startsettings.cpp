#include "startsettings.h"
#include"config.h"
#include"sam.h"

#include <limits.h> // HOST_NAME_MAX

#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>

#include<QIntValidator> // check port

#include<QDesktopWidget> // desktop()
#include<QApplication> // QApplication access

#include<QStringList> // for split reply of sam

#include<QCoreApplication>
#include<QDebug>
#include<QDir>
#include <QFile>
#include<QFileInfo>
#include<QSettings>

#include <QCryptographicHash>





#include"sockets.hpp"
#include"dbmain.hpp"
//#include"messagesdb.h"

#define SAM_DEFAULT_HOST "127.0.0.1"
#define SAM_DEFAULT_PORT 7656

static const char
 * samWork = "<b>OK</b>",
 * samNoWork = "<b>ERROR</b>",
 * samWorkStyleOK = "QLabel {color:green;};",
 * samWorkStyleBad = "QLabel {color:red;};";



inline void StartSettings::setLayouts(void){
    vBox = new QVBoxLayout(this);
    hBox = new QHBoxLayout(this);
    this->setLayout(vBox);
    vBox->addWidget(mainText);
    vBox->addWidget(username);
    vBox->addWidget(password);

    vBox->addLayout(hBox);

    hBox->addWidget(host);
    hBox->addWidget(port);
    hBox->addWidget(OK);
    hBox->addWidget(CheckSAM);

    vBox->addWidget(SAMWork);


}
inline void StartSettings::setLabels(void){
    mainText = new QLabel(this),
    SAMWork = new QLabel(this);

    mainText->setFont(QFont("Arial Black",10));
    SAMWork->setFont(QFont("Arial",12));


    mainText->setAlignment( Qt::AlignCenter );
    SAMWork->setAlignment( Qt::AlignCenter );


    mainText->setText(
    tr("Hello is start settings "
    "Here you should set your SAM "
    "host:port ")
                     );



    SAMWork->hide();
    mainText->show();

}
void StartSettings::Register(void){
    qDebug() << "Register";
    if(username->text().size() > 4 && password->text().size() > 6 && CheckSam() ){
        // TODO: Add files
        //delete this;
        setVisible(false);
        setEnabled(false);

        QFileInfo finfo(QCoreApplication::applicationFilePath());
        std::string pathF = finfo.absoluteDir().currentPath().toStdString() + "/" + CONFIG_PATH;
        qDebug() << pathF.c_str();
        QDir cdir( pathF.c_str() );
        QFile Config( (pathF+"/config.ini").c_str() );


        if(!cdir.exists()){
            qDebug() << pathF.c_str()  << "dir not exist";
            cdir.mkdir(pathF.c_str());
        }
        if(!Config.open(QIODevice::WriteOnly	))
            qCritical() << "Cannot open config file" << CONFIG_PATH << "config.ini";
        Config.close();

        QSettings settings((pathF+"/config.ini").c_str(), QSettings::NativeFormat);
        settings.setValue("SAM/host",host->text());
        settings.setValue("SAM/port",port->text());
        settings.setValue("User/Username",username->text());
        QByteArray passBytes(password->text().toStdString().c_str());
        passBytes.append(username->text().toStdString().c_str()); // salt
        settings.setValue("User/Password",QCryptographicHash::hash(passBytes, QCryptographicHash::Sha1		));


        dbmain db(true);
        while(!db.getInstalled());

        //db.install();
        emit Registered(true);

    }

}

inline void StartSettings::setConnects(void){
    connect(
     CheckSAM,
     SIGNAL(clicked(bool)),
     SLOT( CheckSam() ) );
    connect(OK,SIGNAL(clicked(bool)),
            SLOT( Register() ) );

}

inline void StartSettings::setWindowHint(void){
  //  this->setMinimumHeight(300);
   // this->setMinimumWidth(300);
    this->setWindowTitle( tr("First steps") );
    this->setFixedSize(500,300);

    QRect ScreenRect
         = QApplication::desktop()->screenGeometry();
    this->move(
                ScreenRect.width()/4,
                ScreenRect.height()/4
                );
}



inline void StartSettings::setButtons(void){
    OK = new QPushButton(this),
    CheckSAM = new QPushButton(this);
    OK->setText( tr("OK") );
    CheckSAM->setText( tr("CheckSam") );
}

inline void StartSettings::setLineEdits(void){

    QValidator * isPort
            = new QIntValidator(1, 65535, this);

    host = new QLineEdit(this);
    port = new QLineEdit(this);
    username = new QLineEdit(this);
    password = new QLineEdit(this);


    host->setPlaceholderText( tr("host") );
    port->setPlaceholderText( tr("port") );

    username->setPlaceholderText( tr("username") );
    password->setPlaceholderText( tr("password") );

    password->setEchoMode(QLineEdit::Password);


    port->setValidator(isPort);
    host->setMaxLength(HOST_NAME_MAX);
    username->setMaxLength(30);
    password->setMaxLength(128);

    host->setText(SAM_DEFAULT_HOST);
    port->setText( QString::number(SAM_DEFAULT_PORT) );
}

bool StartSettings::CheckSam(void){
    sam Client((char*)host->text().toStdString().c_str(), atoi( port->text().toStdString().c_str()));
    SAMWork->show();
    if( !Client.getError() )
    {
           SAMWork->setStyleSheet(samWorkStyleOK);
           SAMWork->setText(samWork);
           return true;
    }
    SAMWork->setStyleSheet(samWorkStyleBad);
    SAMWork->setText(samNoWork);
    return false;

}

StartSettings::StartSettings(QWidget *parent) :
    QWidget(parent)
{
        this->setWindowHint();
        this->setLabels();
        this->setButtons();
        this->setLineEdits();
        this->setLayouts();
        this->setConnects();
}

StartSettings::~StartSettings(){
   // delete [] this->vBox;
   // delete [] this->hBox;
}
