#include "ParallaxScrollerItem.h"

#include "ParallaxScrollerStatic.h"

ParallaxScrollerStatic::ParallaxScrollerStatic(QGraphicsScene *scene)
{
    m_parent = scene;
}

ParallaxScrollerStatic::~ParallaxScrollerStatic()
{

}

void ParallaxScrollerStatic::setLayerWidth(int width)
{
    m_layerWidth = width;
}

void ParallaxScrollerStatic::addParallaxScrollItem(const QString &layer, QPointF pos, qreal depth, qreal slowingFactor)
{
    ParallaxScrollerItem* firstPartOfLayer = new ParallaxScrollerItem(layer, QPointF(pos.x(), pos.y()),
                                                                      depth, 1, slowingFactor, m_parent);
    ParallaxScrollerItem* secondPartOfLayer = new ParallaxScrollerItem(layer, QPointF(pos.x()+m_layerWidth, 0),
                                                                       depth, 1, slowingFactor, m_parent);

    m_layersFirstWave.append(firstPartOfLayer);
    m_layerSecondWave.append(secondPartOfLayer);
}
