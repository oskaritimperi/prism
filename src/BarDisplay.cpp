#include <QPainter>

#include "BarDisplay.h"

BarDisplay::BarDisplay(int w, int h) :
    QPixmap(w, h)
{
    m_partCount = 4;
    m_maxValue = 50;
    m_value = 50;

    fill(QColor(Qt::transparent));
}

BarDisplay::~BarDisplay()
{
}

void BarDisplay::initShape()
{
    QPainter p(this);
    QPen pen(QColor(0, 0, 0, 255));
    pen.setWidth(1);

    QBrush brush(m_displayColor);

    p.setPen(pen);
    p.fillRect(0, 0, width(), height(), brush);

    // left side
    p.drawLine(0, 0, 0, height() - 1);
    p.drawLine(0, 0, 20, 0);
    p.drawLine(0, height() - 1, 20, height() - 1);

    // right side
    p.drawLine(width() - 1, 0, width() - 1, height() - 1);
    p.drawLine(width() - 1, 0, width() -1 - 20, 0);
    p.drawLine(width() - 1, height() - 1, width() - 1 - 20, height() - 1);

    pen.setWidth(2);
    p.setPen(pen);
    // the | -lines
    for (int i = 1; i < 4; i++)
        p.drawLine((160 / 3) * i, 0, (160 / 3) * i - 15, height() - 1);
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
