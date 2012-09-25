#ifndef BasicEnemy_h
#define BasicEnemy_h

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "Character.h"

class BasicEnemy : public Character
{
public:
    BasicEnemy(QGraphicsScene* scene, QPointF pos, QGraphicsItem* parent = 0);
    virtual ~BasicEnemy();

    void advance(int phase);

private:

};

#endif // BasicEnemy_h
