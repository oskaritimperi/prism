#include "CircularDisplay.h"

CircularDisplay::CircularDisplay(QGraphicsItem* parent) :
    QGraphicsItem(parent)
{
    m_partCount = 5;
    m_maxValue = 50;
    m_consumeSpeed = 5;
    m_value = 10;
    m_activated = false;

    /* TODO:
        initialize this item with some kind of rounds graphics
        that supports partitioning
    */
}

CircularDisplay::~CircularDisplay()
{
}

void CircularDisplay::advance(int phase)
{
    if (phase == 0)
        return;

    // TODO: consuming logic if color is activated
    if (phase == 1)
    {
        if (m_activated)
            ;
        else
            return;
    }
}

void CircularDisplay::setDisplayColor(QColor col)
{
    m_displayColor = col;
}

void CircularDisplay::collected(int amount)
{
    m_value += amount;
    if (m_value > m_maxValue)
        m_value = m_maxValue;

    updateDisplay();
}

void CircularDisplay::activate()
{
    m_activated = true;
}

void CircularDisplay::unactivate()
{
    m_activated = false;
}

void CircularDisplay::updateDisplay()
{
    // TODO: update graphics so user knows collecting stuff does help
}

QRectF CircularDisplay::boundingRect() const
{
    return QRectF();
}

void CircularDisplay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}
