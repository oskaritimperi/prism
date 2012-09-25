#ifndef Collectible_H
#define Collectible_H

#include "Sprite.h"

class Collectible : public Sprite
{
public:
    Collectible(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    void collected();

    void setValue(int value);
    int getValue() const;

private:
    int m_value;
};

#endif // Collectible_H
