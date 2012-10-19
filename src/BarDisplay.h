#ifndef BarDisplay_h
#define BarDisplay_h

#include <QPixmap>

class BarDisplay : public QPixmap
{
public:
    BarDisplay(int w = 250, int h = 40);
    virtual ~BarDisplay();

    void initShape();

    void collected(int);
    void consumed(int);
    void setDisplayColor(QColor col);
    
signals:
    
public slots:

private:
    int m_partCount;
    int m_value;
    int m_maxValue;
    QColor m_displayColor;

    void updateDisplay();
    
};

#endif // BarDisplay_h
