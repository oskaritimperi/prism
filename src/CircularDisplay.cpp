#include <QPainter>
#include <QDebug>

#include "CircularDisplay.h"

CircularDisplay::CircularDisplay(const QString& name, int w, int h) :
    QPixmap(w, h)
{
    m_partCount = 5;
    m_maxValue = 50;
    m_consumeSpeed = 5;
    m_value = 10;
    m_activated = false;
    m_name = name;

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

    pen.setWidth(4);
    p.setPen(pen);

    // draw base ellipse
    p.drawEllipse(QPointF(25, 35), 20, 20);

    p.setBrush(brush);

    // first 1/4th
    //p.drawPie(5, 15, 40, 20, 0, 180 * 16);

    // last 1/4th
    //p.drawPie(25, 35, 40, 20, 0, -180 * 16);

    // upper half
    //p.drawPie(5, 15, 40, 40, 0, 180 * 16);

    // lower half
    pen.setWidth(2);
    p.setPen(pen);
    p.drawPie(5, 15, 40, 40, 0, -180 * 16);

    // draw "tick" lines
    //p.drawLine(25, 15, 25, 0); // 12 o'clock
    //p.drawLine(45, 35, 60, 35); // 3 o'clock
    //p.drawLine(25, 55, 25, 70); // 6 o'clock
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
    qDebug() << "activated " << m_name;
    m_activated = true;
}

void CircularDisplay::deactivate()
{
    qDebug() << "deactivated " << m_name;
    m_activated = false;
}

bool CircularDisplay::active() const
{
    return m_activated;
}

void CircularDisplay::updateDisplay()
{
    // TODO: update graphics so user knows collecting stuff does help
}
