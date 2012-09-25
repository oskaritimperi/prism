#include "GameView.h"

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    resize(800, 480);
    setWindowTitle("Generic platformer base, version 0.0.1 alpha");

    setCentralWidget(m_gameView->instance());
}

MainWindow::~MainWindow()
{

}
