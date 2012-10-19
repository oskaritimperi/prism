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
}

CircularDisplay::~CircularDisplay()
{
}

void CircularDisplay::initShape()
{
    QPainter p(this);
    QPen pen(QColor(0, 0, 0, 255));
    QBrush brush(m_displayColor);

    pen.setWidth(5);
    p.setPen(pen);
    p.setBrush(brush);

    // draw base ellipse
    p.drawEllipse(QPointF(25, 35), 20, 20);

    // draw "tick" lines
    p.drawLine(25, 15, 25, 0); // 12 o'clock
    p.drawLine(45, 35, 60, 35); // 3 o'clock
    p.drawLine(25, 55, 25, 70); // 6 o'clock
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
