#include "BarDisplay.h"

BarDisplay::BarDisplay(int w, int h) :
    QPixmap(w, h)
{
    m_partCount = 4;
    m_maxValue = 50;
    m_value = 50;

    /* TODO:
        initialize this item with some kind of rectangle graphics
        that supports partitioning, e.g.
        [  /  /  ] or such
    */
}

BarDisplay::~BarDisplay()
{
}

void BarDisplay::collected(int amount)
{
    m_value += amount;

    if (m_value > m_maxValue)
        m_value = m_maxValue;

    updateDisplay();
}

void BarDisplay::consumed(int amount)
{
    m_value -= amount;

    if (m_value < 0)
        m_value = 0;

    updateDisplay();
}

void BarDisplay::setDisplayColor(QColor col)
{
    m_displayColor = col;
}

void BarDisplay::updateDisplay()
{
    // TODO: update graphics so user knows he is hit
}
