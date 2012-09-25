#ifndef ParallaxScrollerStatic_h
#define ParallaxScrollerStatic_h

#include <QStringList>
#include <QPointF>
#include <QGraphicsScene>

class ParallaxScrollerItem;

class ParallaxScrollerStatic
{
public:
    ParallaxScrollerStatic(QGraphicsScene* scene);
    virtual ~ParallaxScrollerStatic();

    void setLayerWidth(int width);
    void addParallaxScrollItem(const QString& layer, QPointF pos, qreal depth, qreal slowingFactor);

private:
    QGraphicsScene* m_parent;
    QVector<ParallaxScrollerItem*> m_layersFirstWave;
    QVector<ParallaxScrollerItem*> m_layerSecondWave;
    int m_layerWidth;
};

#endif // ParallaxScrollerStatic_h
