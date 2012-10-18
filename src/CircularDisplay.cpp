#include <QPainter>
#include "CircularDisplay.h"

CircularDisplay::CircularDisplay(int w, int h) :
    QPixmap(w, h)
{
    m_partCount = 5;
    m_maxValue = 50;
    m_consumeSpeed = 5;
    m_value = 10;
    m_activated = false;

    fill(QColor(Qt::transparent));

    QPainter p(this);
    QPen pen(QColor(0, 0, 0, 255));
    p.setPen(pen);

    // draw base ellipse
    p.drawEllipse(45, 45, 35, 35);

    // draw "tick" lines
    p.drawLine(45, 10, 45, 0); // 12 o'clock
    p.drawLine(62.5, 27.5, 70, 20); // 1.5 o'clock
    p.drawLine(80, 45, 90, 45); // 3 o'clock
    p.drawLine(62.5, 62.5, 70, 70); // 4.5 o'clock
    p.drawLine(45, 80, 80, 90); // 6 o'clock

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
