#ifndef CircularDisplay_h
#define CircularDisplay_h

#include <QPixmap>

class CircularDisplay : public QPixmap
{
public:
    CircularDisplay(int w = 90, int h = 90);
    virtual ~CircularDisplay();

    void setDisplayColor(QColor col);
    void collected(int amount);
    void activate();
    void unactivate();

signals:
    
public slots:

private:
    int m_partCount;
    int m_maxValue;
    int m_value;
    int m_consumeSpeed;
    bool m_activated;
    QColor m_displayColor;

    void updateDisplay();
    
};

#endif // CircularDisplay_h
