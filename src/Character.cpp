#include "Character.h"

Character::Character(QGraphicsItem *parent, QGraphicsScene *scene)
    : Sprite(parent, scene),
      m_healthPoints(10),
      m_shieldCapacity(0),
      m_meleeDamage(5),
      m_rangedDamage(0),
      m_velocityX(0),
      m_velocityY(0),
      m_state(STATE_IDLE)
{

}

Character::~Character()
{
}

void Character::increaseHealthPoints(int hp)
{
    m_healthPoints += hp;
}

void Character::decreaseHealthPoints(int hp)
{
    m_healthPoints -= hp;

    if(m_healthPoints <= 0)
    {
        m_state = STATE_DEAD;
    }
}

void Character::setHealthPoints(int hp)
{
    m_healthPoints = hp;
}

int Character::getHealthPoints()
{
    return m_healthPoints;
}

void Character::increaseShieldCapacity(int shieldCapacity)
{
    m_shieldCapacity += shieldCapacity;
}

void Character::decreaseShieldCapacity(int shieldCapacity)
{
    m_shieldCapacity -= shieldCapacity;
}

void Character::setShieldCapacity(int shieldCapacity)
{
    m_shieldCapacity = shieldCapacity;
}

int Character::getShieldCapacity()
{
    return m_shieldCapacity;
}

void Character::setMeleeDamage(int damage)
{
    m_meleeDamage = damage;
}

int Character::getMeleeDamage()
{
    return m_meleeDamage;
}

void Character::setRangedDamage(int damage)
{
    m_rangedDamage = damage;
}

int Character::getRangedDamage()
{
    return m_rangedDamage;
}

void Character::setVelocityX(int x)
{
    m_velocityX = x;
}

void Character::setVelocityY(int y)
{
    m_velocityY = y;
}

int Character::getVelocityX()
{
    return m_velocityX;
}

int Character::getVelocityY()
{
    return m_velocityY;
}

void Character::setState(State s)
{
    m_state = s;
}

State Character::getState()
{
    return m_state;
}
