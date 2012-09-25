#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QSettings>
#include <QDebug>

#include "Hero.h"
#include "GameScene.h"

Hero::Hero(QGraphicsScene* scene, QPointF pos, QGraphicsItem* parent)
    : Character(parent, scene)
{
    m_state = STATE_IDLE;

    // something small for testing purposes
    setHealthPoints(15);

    setPos(pos);
    setZValue(2);

    setShapeMode(QGraphicsPixmapItem::MaskShape);
}

Hero::~Hero()
{
}

void Hero::advance(int phase)
{
    Character::advance(phase);

    if (phase == 0)
        return;

    // err, no good.
    if(m_state == STATE_DEAD)
    {
        gameOver();
        //removeMe();
    }
}
