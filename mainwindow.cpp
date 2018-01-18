#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"config.h"
#include"sam.h"

#include<QDesktopWidget>
#include<QMessageBox>
#include<QFileInfo>
#include<QDir>
#include<QFileDialog>
#include<QDebug>
#include"sockets.hpp"

void MainWindow::changeChat(QListWidgetItem * item){
    qDebug() << "Open chat with" << item->text();
    QList<QString> * msgs = db.getMessages(item->text().toStdString().c_str());//dbmain::getMessages
    QList<QString>::iterator iterator;
    this->myUi->textBrowser->setText("");
    for(iterator = msgs->begin();iterator!=msgs->end();iterator++){
        this->myUi->textBrowser->setText(myUi->textBrowser->toPlainText() + *iterator);
    }

}



void MainWindow::ClientThread(int socket){
    MyOwnTCPSocket::Write(socket, "hello");
}


void MainWindow::ClientAccepting(void){
/*
    while(1){
    sam Client(config->value("SAM/host").toString().toStdString().c_str(),
               atoi( config->value("SAM/port").toString().toStdString().c_str()));
    Client.loadKeys(config->value("SAM/Pubkey").toString().toStdString().c_str(),config->value("SAM/Privkey").toString().toStdString().c_str());

    if( !Client.accept() ) continue;
    qDebug() << "Accepting" << Client.getIncoming();
    int S = Client[Client.getIncoming()-1];

    qDebug() << MyOwnTCPSocket::Read(S) << " Connected";
    std::thread(&MainWindow::ClientThread,this,S);

    if(Client.getError()) continue;

    }
*/


}



/*
static void * FriendAccepting(void * self){
    MainWindow * w = reinterpret_cast<MainWindow*>(self);
    while(1){
    sam Client(w->config->value("SAM/host").toString().toStdString().c_str(),
               atoi( w->config->value("SAM/port").toString().toStdString().c_str()));
    if(Client.getError()) continue;

    }
    return self;
}

static void * MessageAccepting(void * self){
    MainWindow * w = reinterpret_cast<MainWindow*>(self);
    while(1){
    sam Client(w->config->value("SAM/host").toString().toStdString().c_str(),
               atoi( w->config->value("SAM/port").toString().toStdString().c_str()));
    if(Client.getError()) continue;


    }
    return self;
}
*/


void MainWindow::initFriendList(void){
  /*
    FriendList->move(0,30);
    FriendList->resize(120,this->height());
    FriendList->setStyleSheet("QListWidget {color:blue;background-color:snow;}");
    new QListWidgetItem(tr("Self"), FriendList);

    mhLayout->addWidget(FriendList);
*/
    db.query("SELECT * FROM Friends;");
    int index;

    while(db.q.next()){
       index = db.q.record().indexOf("nick");
       this->myUi->listWidget->addItem(db.q.value(index).toString());
    }
    connect(myUi->listWidget,
            SIGNAL(itemClicked(QListWidgetItem*)),
                   this,
                   SLOT(changeChat(QListWidgetItem*)) );

    QListWidgetItem tmp;
    tmp.setText("Self");
    this->changeChat(&tmp);

}

void MainWindow::setBackground(void){
    qDebug() << "Set background";

    QFileDialog filedialog(this);

    filedialog.setFileMode(QFileDialog::ExistingFile);
    filedialog.setNameFilter(tr("jpg file (*.jpg)"));
    if(filedialog.exec()){
        QStringList imgs = filedialog.selectedFiles();
        qDebug() << "File: " << imgs[0];
        FILE * from, *to;
        from = fopen(imgs[0].toStdString().c_str(), "rb");
        to = fopen( (pathF+"/background.jpg").c_str(),"wb" );
        fseek(from,SEEK_END,0);
        unsigned long fsize = ftell(from);
        rewind(from); // fseek(from,SEEK_SET,0);
        char * buffer = new char[fsize+1];
        while( fread(buffer,fsize,1, from)  ){
            fwrite(buffer,fsize,1,to);
            memset(buffer,0,fsize);
        }
        delete [] buffer;
        fclose(from);
        fclose(to);
        this->myUi->centralwidget->setStyleSheet( this->myUi->centralwidget->styleSheet()  );

    }
}

void MainWindow::initMessageBox(void){
    /*
    MessageWindow = new QTextEdit(this);
    MessageWindow->setReadOnly(true);
    MessageWindow->setText("Check                                                              "
                           "         test 123123");
    MessageWindow->setWordWrapMode( QTextOption::WordWrap		);
    MessageWindow->setAlignment(    Qt::AlignTop | Qt::AlignLeft);
    MessageWindow->setGeometry(125,30,this->width()-330,this->height()-100);
    MessageWindow->setStyleSheet("QTextEdit {background-color:snow;}");

    mhLayout->addWidget(MessageWindow);
*/
}

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

    Settings_background = new QAction(this);
    Settings_background->setText(tr("Set background"));
    Settings->addAction(Settings_Network);
    Settings->addAction(Settings_background);

    connect( Settings_background, SIGNAL(triggered()), this, SLOT(setBackground()) );



    //advance
    Advance_Exit = new QAction(this);
    Advance_About = new QAction(this);

    Advance_Exit->setShortcut(QKeySequence(tr("Ctrl+F4")));
    Advance_Exit->setStatusTip( tr("Exit from program") );
    Advance_Exit->setText( tr("&Exit") );

    Advance_About->setShortcut(QKeySequence(tr("F1")));
    Advance_About->setStatusTip(tr("About of program"));
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
/*
     FriendList = new QListWidget(this);
     // FriendList->addItem();
     // ...
     mhLayout = new QHBoxLayout(this);

     this->setLayout(mhLayout);
*/

}

void MainWindow::SessionThread(){
    while(1){
        sam Client(config->value("SAM/host").toString().toStdString().c_str(),
                   atoi( config->value("SAM/port").toString().toStdString().c_str()));
        Client.loadKeys(config->value("SAM/Pubkey").toString().toStdString().c_str(),config->value("SAM/Privkey").toString().toStdString().c_str());
        Client.CreateSession();
        if( !Client.getError() )continue;
        //while(1);
        Client.WhileSession();
    }

}

void MainWindow::setActiv(){
    this->show();
    QFileInfo finfo(QCoreApplication::applicationFilePath());
    pathF = finfo.absoluteDir().currentPath().toStdString();

    config = new QSettings((pathF + "/" + CONFIG_PATH + "/config.ini").c_str(), QSettings::NativeFormat);
    if(config->value("SAM/Privkey",0) == 0){
        qDebug() << "SAM/Privkey not exist";
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
             Client.CreateSession();

             if(!Client.getError()){
                 config->setValue("SAM/Privkey", Client.getPrivkey());
                 config->setValue("SAM/Pubkey", Client.getPubkey());
                 if(config->value("SAM/Privkey",0) != 0) break;
             }

             QMessageBox error;
             error.setText(tr("Error with SAM, try new"));
             error.exec();
         }
         delete  config;
         config = new QSettings((pathF + "/" + CONFIG_PATH + "/config.ini").c_str(), QSettings::NativeFormat);
    }
    //qDebug() << "PASS OF GUY=" << PassOfGuy;
    this->initFriendList();
    this->initMessageBox();
    this->setStyleSheet("QWidget { background-image: url('./background.jpeg'); }");//background-size:cover;background-position:center;
    db = dbmain();
   // pthread_create(&message_t, 0, &MessageAccepting, this);
   // pthread_create(&friend_t, 0, &FriendAccepting, this);


    client_accepting_t = std::thread(&MainWindow::ClientAccepting, this);
    session_t = std::thread(&MainWindow::SessionThread, this);

}

void MainWindow::resizeEvent(QResizeEvent * e){
    QMainWindow::resizeEvent(e);
}




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    myUi(new Ui::MainWindow)

{
    myUi->setupUi(this);
    myUi->centralwidget->setMinimumSize(551,461);
    myUi->centralwidget->setLayout(this->myUi->horizontalLayout);

    this->setWindowTitle("ISIS-Messenger");

    QRect ScreenRect
         = QApplication::desktop()->screenGeometry();

    this->initMenu();
    this->setGeometry(ScreenRect.width()/4,ScreenRect.height()/4,500,500);
}

MainWindow::~MainWindow()
{
    //delete [] config;
    delete [] myUi;
}
