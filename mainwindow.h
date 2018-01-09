#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMenuBar>
#include<QSettings>




class MainWindow : public QMainWindow
{
    Q_OBJECT


private:
    void initMenu(void);
private:

    QMenu * Friends, * Settings, * Advance;

    QAction * Friends_add,
    * Settings_Network,
    * Advance_Exit, * Advance_About;

    QSettings * config;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void setActiv(void);

private:
};

#endif // MAINWINDOW_H
