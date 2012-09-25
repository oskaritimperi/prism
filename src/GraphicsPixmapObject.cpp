#include "GraphicsPixmapObject.h"

GraphicsPixmapObject::GraphicsPixmapObject(const QPixmap &pixmap,
                                           QGraphicsItem *parent) :
    QGraphicsPixmapItem(pixmap, parent)
{
}
