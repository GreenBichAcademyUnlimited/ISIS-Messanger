#include "enterwidget.h"
#include<QFileInfo>
#include<QDir>
#include<QCoreApplication>
#include<QDebug>
#include"config.h"
#include <QCryptographicHash>

void enterWidget :: NeedNewAccount(void){
    emit NewAccount();
    hide();
}

bool enterWidget :: PassCheck(void){
    QByteArray passBytes(password->text().toStdString().c_str());
    passBytes.append(settings->value("User/Username").toString()); //salt

    QByteArray EndedPass = QCryptographicHash::hash(passBytes, QCryptographicHash::Sha1);
    if ( EndedPass == settings->value("User/Password") ){
        PassOfGuy = (char*)calloc(password->text().toStdString().size()+1,1);
        UsernameOfGuy = (char*)calloc(settings->value("User/Username").toString().toStdString().size()+1,1);
        strcpy(PassOfGuy, settings->value("User/Username").toString().toStdString().c_str() );

        emit PassCorrect();
        setVisible(false);
        return true;
    }
    qDebug() << EndedPass << "!=" << settings->value("User/Password").toString();
    correctly->show();
    correctly->setText(tr("<HTML><b style='color:red'>Not correctly</b></HTML>"));

    return false;
}

enterWidget::~enterWidget(){
}

enterWidget::enterWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(500,300);
    this->setWindowTitle("Account check");
    vbox = new QVBoxLayout (this);
    hbox = new QHBoxLayout (this);

    password = new QLineEdit (this);
    password->setPlaceholderText("your password of account");

    okbtn = new QPushButton(this);
    newAcc = new QPushButton(this);

    correctly = new QLabel(this);
    correctly->setText(tr("<HTML><b style='color:brown'>Click and check:)</b></HTML>"));

    setLayout(vbox);
    vbox->addWidget(password);
    vbox->addLayout(hbox);
    hbox->addWidget(okbtn);
    hbox->addWidget(correctly);

    password->setPlaceholderText(tr("password"));
    (*password).setEchoMode(QLineEdit::Password);
    okbtn->setText("OK");
    newAcc->setText(tr("Create new account"));
    vbox->addWidget(newAcc);

    QFileInfo finfo(QCoreApplication::applicationFilePath());
    std::string pathF = finfo.absoluteDir().currentPath().toStdString() + "/" + CONFIG_PATH;
    settings = new QSettings((pathF+"/config.ini").c_str(), QSettings::NativeFormat);
    connect(okbtn,SIGNAL(clicked(bool)),SLOT(PassCheck()));
    connect(newAcc,SIGNAL(clicked(bool)),SLOT(NeedNewAccount()));




}

