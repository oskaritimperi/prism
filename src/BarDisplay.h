#ifndef BarDisplay_h
#define BarDisplay_h

#include <QPixmap>

class BarDisplay : public QPixmap
{
public:
    BarDisplay();
    virtual ~BarDisplay();

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
