#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMenuBar>



class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QMenu * Advance;
    QAction * Exit;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void setActiv(void){
        this->show();
    }

private:
};

#endif // MAINWINDOW_H
