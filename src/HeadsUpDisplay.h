#ifndef HeadsUpDisplay_h
#define HeadsUpDisplay_h
#include <QObject>
#include <QPixmap>

class QGraphicsScene;
class BarDisplay;
class CircularDisplay;

class HeadsUpDisplay : public QObject, public QPixmap
{
    Q_OBJECT
public:
    HeadsUpDisplay(int w, int h, QGraphicsScene* anchorScene, QObject *parent = 0);
    virtual ~HeadsUpDisplay();

    void update();

    CircularDisplay* redDisplay() const;
    CircularDisplay* greenDisplay() const;
    CircularDisplay* blueDisplay() const;
    BarDisplay* healthDisplay() const;

    void toggleRedColor();
    void toggleGreenColor();
    void toggleBlueColor();
    
signals:
    
public slots:

private:
    QGraphicsScene* m_anchorScene;
    BarDisplay* m_healtBar;
    CircularDisplay* m_redColor;
    CircularDisplay* m_greenColor;
    CircularDisplay* m_blueColor;
    
};

#endif // HeadsUpDisplay_h
