#include "enterwidget.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QFileInfo>
#include<QDir>
#include<QCoreApplication>
#include<QDebug>
#include"config.h"
#include <openssl/sha.h>

void enterWidget :: NeedNewAccount(void){
    emit NewAccount();
    hide();
}

bool enterWidget :: PassCheck(void){
    unsigned char hash[SHA512_DIGEST_LENGTH];
    SHA512((const unsigned char *)password->text().toStdString().c_str(),password->text().size()-1,hash);
    QString EndedPass((const char*)hash);
    if ( EndedPass.toUtf8().toBase64() == settings->value("User/Password").toString().toUtf8().toBase64()){
        emit PassCorrect();
        return true;
    }
    qDebug() << EndedPass.toUtf8().toBase64() << "!=" << settings->value("User/Password").toString().toUtf8().toBase64();
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
    QVBoxLayout vbox(this);
    QHBoxLayout hbox(this);

    password = new QLineEdit (this);
    password->setPlaceholderText("your password of account");

    okbtn = new QPushButton(this);
    newAcc = new QPushButton(this);

    correctly = new QLabel(this);
    correctly->setText(tr("<HTML><b style='color:brown'>Click and check:)</b></HTML>"));

    setLayout(&vbox);
    vbox.addWidget(password);
    vbox.addLayout(&hbox);
    hbox.addWidget(okbtn);
    hbox.addWidget(correctly);

    password->setPlaceholderText(tr("password"));
    (*password).setEchoMode(QLineEdit::Password);
    okbtn->setText("OK");
    newAcc->setText(tr("Create new account"));
    vbox.addWidget(newAcc);

    QFileInfo finfo(QCoreApplication::applicationFilePath());
    std::string pathF = finfo.absoluteDir().currentPath().toStdString() + "/" + CONFIG_PATH;
    settings = new QSettings((pathF+"/config.ini").c_str(), QSettings::NativeFormat);
    connect(okbtn,SIGNAL(clicked(bool)),SLOT(PassCheck()));
    connect(newAcc,SIGNAL(clicked(bool)),SLOT(NeedNewAccount()));

    setVisible(true);



}

