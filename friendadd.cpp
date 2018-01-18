#include "friendadd.h"
#include "ui_friendadd.h"

FriendAdd::FriendAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendAdd)
{
    ui->setupUi(this);
}

FriendAdd::~FriendAdd()
{
    delete ui;
}
