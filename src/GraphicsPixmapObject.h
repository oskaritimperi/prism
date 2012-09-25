#ifndef GraphicsPixmapObject_h
#define GraphicsPixmapObject_h

#include <QObject>
#include <QGraphicsPixmapItem>

/**
  * Used for the animation in SceneChanger. As QPropertyAnimation uses
  * Qt's property system, we have to derive from QObject to use properties.
  * So GraphicsPixmapObject derives from QObject and QGraphicsPixmapItem
  * and publishes the opacity as a property.
  */
class GraphicsPixmapObject : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity);
    Q_PROPERTY(QPointF pos READ pos WRITE setPos);

public:
    explicit GraphicsPixmapObject(const QPixmap &pixmap,
                                  QGraphicsItem *parent = 0);

signals:

public slots:

};

#endif // GraphicsPixmapObject_h
