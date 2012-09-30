#include "CircularDisplay.h"

CircularDisplay::CircularDisplay() :
    QPixmap()
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
