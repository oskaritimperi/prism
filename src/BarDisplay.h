#ifndef BarDisplay_h
#define BarDisplay_h

#include <QGraphicsItem>

class BarDisplay : public QGraphicsItem
{
public:
    BarDisplay(QGraphicsItem* parent = 0);
    virtual ~BarDisplay();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

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
