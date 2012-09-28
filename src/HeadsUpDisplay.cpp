#include "BarDisplay.h"
#include "CircularDisplay.h"

#include "HeadsUpDisplay.h"

HeadsUpDisplay::HeadsUpDisplay(QGraphicsScene* anchorScene, QObject *parent) :
    QObject(parent)
{
    m_healtBar = new BarDisplay();
    m_healtBar->setDisplayColor(QColor(0, 255, 255));
    m_redColor = new CircularDisplay();
    m_redColor->setDisplayColor(QColor(255, 0, 0));
    m_greenColor = new CircularDisplay();
    m_greenColor->setDisplayColor(QColor(0, 255, 0));
    m_blueColor = new CircularDisplay();
    m_blueColor->setDisplayColor(QColor(0, 0, 255));
}

HeadsUpDisplay::~HeadsUpDisplay()
{

}
