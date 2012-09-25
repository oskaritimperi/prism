#ifndef ParallaxScrollerItem_h
#define ParallaxScrollerItem_h

#include <QGraphicsPixmapItem>

class ParallaxScrollerItem : public QGraphicsPixmapItem
{
public:
    ParallaxScrollerItem(QString layer, QPointF pos,
                        qreal depthFactor, qreal speed,
                        qreal factor, QGraphicsScene* scene,
                        QGraphicsItem* parent = 0);
    virtual ~ParallaxScrollerItem();

    void advance(int phase);

private:
    int m_scrollingSpeedSlowingFactor;
    int m_factor;
    qreal m_scrollSpeed;
    QPixmap m_layer;
};

#endif // ParallaxScrollerItem_h
