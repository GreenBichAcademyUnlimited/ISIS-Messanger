#ifndef STARTSETTINGS_H
#define STARTSETTINGS_H

#include <QWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>

class StartSettings : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout * vBox;
    QHBoxLayout * hBox;
    QLabel * mainText , * SAMWork;
    QLineEdit *host, *port, *username, *password;
    QPushButton * OK ,* CheckSAM ;


private:
    void setLayouts(void);
    void setWindowHint(void);
    void setLabels(void);
    void setButtons(void);
    void setLineEdits(void);
    void setConnects(void);

public:
    explicit StartSettings(QWidget *parent = 0);
    ~StartSettings();
signals:


private slots:
    bool CheckSam(void);
};

#endif // STARTSETTINGS_H
