#ifndef MainWindow_h
#define MainWindow_h

#include <QMainWindow>

class GameView;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

signals:

public slots:

private:
    GameView* m_gameView;
};

#endif // MainWindow_h
