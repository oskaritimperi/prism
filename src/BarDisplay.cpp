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
    QBrush brush(m_displayColor);

    p.setPen(Qt::NoPen);
    p.setBrush(brush);

    QPolygon one;
    one.append(QPoint(0, 0));
    one.append(QPoint(0, height() - 1));
    one.append(QPoint((160 / 3 * 1), height()));
    one.append(QPoint((160 / 3 * 1), 0));
    m_healthIndicators.append(one);

    QPolygon two;
    two.append(QPoint(0, 0));
    two.append(QPoint(0, height() - 1));
    two.append(QPoint((160 / 3 * 2), height()));
    two.append(QPoint((160 / 3 * 2), 0));
    m_healthIndicators.append(two);

    QPolygon three;
    three.append(QPoint(0, 0));
    three.append(QPoint(0, height() - 1));
    three.append(QPoint((160 / 3 * 3), height()));
    three.append(QPoint((160 / 3 * 3), 0));
    m_healthIndicators.append(three);

    QPolygon four;
    four.append(QPoint(0, 0));
    four.append(QPoint(0, height() - 1));
    four.append(QPoint(width() - 1, height()));
    four.append(QPoint(width() - 1, 0));
    m_healthIndicators.append(four);

    p.drawPolygon(three);

    p.setBrush(Qt::NoBrush);

    pen.setWidth(2);
    p.setPen(pen);
    // lefttside
    p.drawLine(0, 1, 20, 0);
    p.drawLine(1, 0, 0, height() - 1);
    p.drawLine(0, height() - 1, 20, height() - 1);

    // right side
    p.drawLine(width() - 1, 1, width() -1 - 20, 1);
    p.drawLine(width() - 1, 0, width() - 1, height() - 1);
    p.drawLine(width() - 1, height() - 1, width() - 1 - 20, height() - 1);

    pen.setWidth(2);
    p.setPen(pen);
    // the | -lines
    for (int i = 1; i < 4; i++)
        p.drawLine((160 / 3) * i, 4, (160 / 3) * i, height() - 1 - 5);
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
