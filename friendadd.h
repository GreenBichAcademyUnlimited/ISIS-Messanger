#ifndef FRIENDADD_H
#define FRIENDADD_H

#include <QDialog>

namespace Ui {
class FriendAdd;
}

class FriendAdd : public QDialog
{
    Q_OBJECT

public:
    explicit FriendAdd(QWidget *parent = 0);
    ~FriendAdd();

private:
    Ui::FriendAdd *ui;
};

#endif // FRIENDADD_H
