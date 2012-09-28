#ifndef CircularDisplay_h
#define CircularDisplay_h

#include <QGraphicsItem>

class CircularDisplay : public QGraphicsItem
{
public:
    CircularDisplay(QGraphicsItem* parent = 0);
    virtual ~CircularDisplay();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void advance(int phase);

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
