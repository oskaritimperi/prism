#include <QPainter>
#include <QRgb>
#include "BarDisplay.h"
#include "CircularDisplay.h"

#include "HeadsUpDisplay.h"

HeadsUpDisplay::HeadsUpDisplay(int w, int h, QGraphicsScene *anchorScene, QObject *parent) :
    QPixmap(w, h), QObject(parent)
{
    fill(QColor(Qt::transparent));
    m_healtBar = new BarDisplay(200, 40);
    m_healtBar->setDisplayColor(QColor(255, 204, 51, 127));
    m_healtBar->initShape();

    m_redColor = new CircularDisplay("red", 70, 70);
    m_redColor->setDisplayColor(QColor(127, 0, 0, 127));
    m_redColor->initShape();

    m_greenColor = new CircularDisplay("green", 70, 70);
    m_greenColor->setDisplayColor(QColor(0, 127, 0, 127));
    m_greenColor->initShape();

    m_blueColor = new CircularDisplay("blue", 70, 70);
    m_blueColor->setDisplayColor(QColor(0, 0, 127, 127));
    m_blueColor->initShape();

    m_anchorScene = anchorScene;

    QPainter p(this);

    p.drawPixmap(10, 20, *m_redColor);
    p.drawPixmap(10, 120, *m_greenColor);
    p.drawPixmap(10, 220, *m_blueColor);
    p.drawPixmap(300, 430, *m_healtBar);
}

HeadsUpDisplay::~HeadsUpDisplay()
{

}

void HeadsUpDisplay::update()
{
    m_healtBar->updateDisplay();
    m_redColor->updateDisplay();
    m_greenColor->updateDisplay();
    m_blueColor->updateDisplay();
}

CircularDisplay *HeadsUpDisplay::redDisplay() const
{
    return m_redColor;
}

CircularDisplay *HeadsUpDisplay::greenDisplay() const
{
    return m_greenColor;
}

CircularDisplay *HeadsUpDisplay::blueDisplay() const
{
    return m_blueColor;
}

BarDisplay *HeadsUpDisplay::healthDisplay() const
{
    return m_healtBar;
}

void HeadsUpDisplay::toggleRedColor()
{
    if (m_redColor->active())
        m_redColor->deactivate();
    else
        m_redColor->activate();
}

void HeadsUpDisplay::toggleGreenColor()
{
    if (m_greenColor->active())
        m_greenColor->deactivate();
    else
        m_greenColor->activate();
}

void HeadsUpDisplay::toggleBlueColor()
{
    if (m_blueColor->active())
        m_blueColor->deactivate();
    else
        m_blueColor->activate();
}
