#include "GameView.h"

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    resize(800, 480);
    setWindowTitle("prism, version 0.0.3");

    setCentralWidget(m_gameView->instance());
}

MainWindow::~MainWindow()
{

}
