#ifndef Hero_h
#define Hero_h

#include "Character.h"

class Hero: public Character
{
    Q_OBJECT

public:
    Hero(QGraphicsScene* scene, QPointF pos, QGraphicsItem* parent = 0);
    virtual ~Hero();

    void advance(int phase);

signals:
    void gameOver();
    void levelComplete();
    void updateUI();

private:

};

#endif // Hero_h
