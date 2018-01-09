#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)

{
    Advance = new QMenu(this);
    Exit = new QAction(this);
    Exit->setShortcut(QKeySequence(tr("Ctrl+F4")));
    Exit->setStatusTip("Exit from program");
    Exit->setText("Exit");
    connect(Exit,SIGNAL(triggered(bool)),this,SLOT(close()));

    Advance = menuBar()->addMenu(tr("Advance"));
    Advance->addAction(Exit);
}

MainWindow::~MainWindow()
{

}
