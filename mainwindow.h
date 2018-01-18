#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMenuBar>
#include<QSettings>
#include<QLabel>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QListWidget>
#include<QTextEdit>
#include<QResizeEvent>
#include"dbmain.hpp"
#include<thread>

namespace Ui{
    class MainWindow;
};

class MainWindow :        public QMainWindow
{
    Q_OBJECT


private:
    void initMenu(void);
    void initFriendList(void);
    void initMessageBox(void);
    void resizeEvent(QResizeEvent *event);

    //
    void ClientAccepting(void);
    void ClientThread(int socket);
    void SessionThread(void);

private:
    std::thread client_accepting_t, session_t;

    std::string pathF;

    Ui::MainWindow * myUi;

    QMenu * Friends, * Settings, * Advance;

    QAction * Friends_add,
    * Settings_Network, * Settings_background,
    * Advance_Exit, * Advance_About;

    QSettings * config;

    dbmain db;
    /*
    QVBoxLayout * mvLayout;
    QHBoxLayout * mhLayout;
    QListWidget * FriendList;
    QTextEdit * MessageWindow;
*/



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void setActiv(void);
private slots:
    void setBackground(void);
    void changeChat(QListWidgetItem*);

};

#endif // MAINWINDOW_H
