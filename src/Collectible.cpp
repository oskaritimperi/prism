#include "Collectible.h"

#include <QSettings>

Collectible::Collectible(QGraphicsItem *parent, QGraphicsScene *scene)
    : Sprite(parent, scene)
{

}

void Collectible::collected()
{
    setData(0, "colllected");
    removeMe();
}

void Collectible::setValue(int value)
{
    m_value = value;
}

int Collectible::getValue() const
{
    return m_value;
}
