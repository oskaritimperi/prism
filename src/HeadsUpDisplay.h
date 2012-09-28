#ifndef HeadsUpDisplay_h
#define HeadsUpDisplay_h
#include <QObject>

class QGraphicsScene;
class BarDisplay;
class CircularDisplay;

class HeadsUpDisplay : public QObject
{
    Q_OBJECT
public:
    HeadsUpDisplay(QGraphicsScene* anchorScene, QObject *parent = 0);
    virtual ~HeadsUpDisplay();
    
signals:
    
public slots:

private:
    BarDisplay* m_healtBar;
    CircularDisplay* m_redColor;
    CircularDisplay* m_greenColor;
    CircularDisplay* m_blueColor;
    
};

#endif // HeadsUpDisplay_h
