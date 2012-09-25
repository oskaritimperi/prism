#include "ParallaxScrollerItem.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QScrollBar>

#include <QPainter>
#include <QDebug>

ParallaxScrollerItem::ParallaxScrollerItem(QString layer, QPointF pos,
                                           qreal depthFactor, qreal speed,
                                           qreal factor, QGraphicsScene *scene,
                                           QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent, scene), m_scrollSpeed(speed), m_factor(factor)
{
    m_scrollingSpeedSlowingFactor = 0;
    m_layer.load(layer);
    setPixmap(m_layer);
    setPos(pos);
    setZValue(depthFactor);
}

ParallaxScrollerItem::~ParallaxScrollerItem()
{

}

void ParallaxScrollerItem::advance(int phase)
{
    if(phase == 1)
    {
        m_scrollingSpeedSlowingFactor++;
        if(m_scrollingSpeedSlowingFactor % m_factor == 0)
        {
            m_scrollingSpeedSlowingFactor = 0;
            setPos(x()-m_scrollSpeed, y());

            QGraphicsView* v = scene()->views().first();
            QPointF p = v->mapToScene(v->viewport()->x(), 0);

            if(x() <= p.x()-pixmap().width())
            {
                setPos(p.x()+pixmap().width()-m_scrollSpeed, y());
            }
        }
    }
}
