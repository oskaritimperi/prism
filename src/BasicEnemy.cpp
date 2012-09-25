#include <QGraphicsScene>
#include <QApplication>
#include <QDebug>

#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(QGraphicsScene* scene, QPointF pos, QGraphicsItem* parent)
    : Character(parent, scene)
{
    m_velocityY = 0;
    m_velocityX = 1;

    setPos(pos);
    setZValue(2);
    setShapeMode(QGraphicsPixmapItem::MaskShape);
}

BasicEnemy::~BasicEnemy()
{

}

void BasicEnemy::advance(int phase)
{
	if(phase == 0)
        return;

	if(m_state == STATE_DEAD)
	{
		qDebug() << "this baddy be dead now";
		removeMe();
	}

    if(phase == 1)
    {
        return;
    }
}
