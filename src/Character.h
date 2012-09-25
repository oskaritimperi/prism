#ifndef Character_h
#define Character_h

#include "Sprite.h"

enum State
{
    STATE_IDLE,
    STATE_MOVING_RIGHT,
    STATE_MOVING_LEFT,
    STATE_DEAD,
    STATE_JUMPING,
    STATE_LANDING,
    STATE_JUMPING_DOUBLE,
    STATE_LANDING_DOUBLE_FORCE,
    STATE_SPRINTING_RIGHT,
    STATE_SPRINTING_LEFT,
    STATE_CLIMB_UP,
    STATE_CLIMG_DOWN
};

class Character: public Sprite
{
public:
    explicit Character(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    virtual ~Character();

    void increaseHealthPoints(int);
    void decreaseHealthPoints(int);
    void setHealthPoints(int);
    int getHealthPoints();

    void increaseShieldCapacity(int);
    void decreaseShieldCapacity(int);
    void setShieldCapacity(int);
    int getShieldCapacity();

    void setMeleeDamage(int);
    int getMeleeDamage();

    void setRangedDamage(int);
    int getRangedDamage();

    void setVelocityX(int);
    void setVelocityY(int);
    int getVelocityX();
    int getVelocityY();

    void setState(State);
    State getState();

protected:
    int m_healthPoints;
    int m_shieldCapacity;

    int m_meleeDamage;
    int m_rangedDamage;

    int m_velocityX;
    int m_velocityY;

    State m_state;
};

#endif // Character_h
