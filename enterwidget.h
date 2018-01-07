#ifndef ENTERWIDGET_H
#define ENTERWIDGET_H

#include <QWidget>
#include<QSettings>
#include<QLineEdit>
#include<QPushButton>
#include<QLabel>



class enterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit enterWidget(QWidget *parent = 0);
    ~enterWidget();
private:
    QString actualPassword;
    QSettings * settings;
    QLineEdit * password;
    QPushButton * okbtn, *newAcc;
    QLabel * correctly;
signals:
    void PassCorrect(void);
    void NewAccount(void);
public slots:
    bool PassCheck(void);
    void NeedNewAccount();

};

#endif // ENTERWIDGET_H
