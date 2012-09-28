#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QFontMetrics>

#include "GraphicsButtonObject.h"

QPixmap *GraphicsButtonObject::s_tmpGfx = 0;
int GraphicsButtonObject::s_ref = 0;

GraphicsButtonObject::GraphicsButtonObject(const QPixmap &releasedPixmap,
                                           QGraphicsPixmapItem *parent,
                                           QGraphicsScene *scene)
                                               : QObject(0),
                                               QGraphicsPixmapItem(releasedPixmap, parent, scene)

{
    s_ref++;
    m_releasedGfx = releasedPixmap;
}

GraphicsButtonObject::GraphicsButtonObject(QGraphicsPixmapItem *parent,
                                           QGraphicsScene *scene)
                                               : QObject(0),
                                               QGraphicsPixmapItem(parent, scene)

{
    s_ref++;
}

GraphicsButtonObject::GraphicsButtonObject(const QString &str,
                                           QGraphicsPixmapItem *parent,
                                           QGraphicsScene *scene)
                                               : QObject(0),
                                               QGraphicsPixmapItem(parent, scene)
{
    s_ref++;

    int pw = 280;
    int ph = 60;

    // Draw the gradients only once
    if (!s_tmpGfx)
    {
        //DBG("generating button gradients");

        s_tmpGfx = new QPixmap(pw, ph);
        QPainter painter(s_tmpGfx);

        painter.setPen(Qt::NoPen);

        painter.setBrush(Qt::white);
        painter.drawRect(s_tmpGfx->rect());

        QLinearGradient grad;

        grad.setCoordinateMode(QGradient::ObjectBoundingMode);

        grad.setStart(0, 0);
        grad.setFinalStop(0, 1);

        /*
        grad.setColorAt(0, Qt::white);
        grad.setColorAt(0.20, QColor(137, 175, 201));
        grad.setColorAt(0.35, QColor(35, 136, 207));
        grad.setColorAt(0.5, QColor(32, 98, 145));
        grad.setColorAt(0.65, QColor(35, 136, 207));
        grad.setColorAt(0.80, QColor(137, 175, 201));
        grad.setColorAt(1, Qt::white);
        */

        grad.setColorAt(0, Qt::red);
        grad.setColorAt(0.20, QColor(255, 127, 0));
        grad.setColorAt(0.35, QColor(255, 255, 0));
        grad.setColorAt(0.5, QColor(0, 255, 0));
        grad.setColorAt(0.65, QColor(0, 0, 255));
        grad.setColorAt(0.80, QColor(111, 0, 255));
        grad.setColorAt(1, QColor(143, 0, 255));

        painter.setBrush(QBrush(grad));
        painter.drawRect(4, 4, pw-8, ph-8);
    }

    QPixmap released = QPixmap(*s_tmpGfx);
    QPainter painter(&released);

    QFont font("Arial", 36);
    font.setLetterSpacing(QFont::PercentageSpacing, 95);

    QFontMetrics metrics(font);
    QRect bbox = metrics.boundingRect(str);

    QPainterPath path;

    int x = (ph - metrics.height()) / 2;
    path.addText(pw/2-bbox.width()/2, x + metrics.ascent(),  font, str);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 3));
    painter.setBrush(Qt::white);
    painter.drawPath(path);

    QPixmap pressed(released);

    QPainter painter2(&pressed);
    painter2.setBrush(QColor(0, 0, 0, 127));
    painter2.drawRect(pressed.rect());

    m_releasedGfx = released;
    m_pressedGfx = pressed;

    setPixmap(released);
}

GraphicsButtonObject::~GraphicsButtonObject()
{
    s_ref--;

    if (s_tmpGfx && s_ref == 0)
    {
        delete s_tmpGfx;
        s_tmpGfx = 0;
    }
}

void GraphicsButtonObject::setPressedPixmap(const QPixmap &pixmap)
{
    m_pressedGfx = pixmap;
}

void GraphicsButtonObject::setReleasedPixmap(const QPixmap &pixmap)
{
    m_releasedGfx = pixmap;
}

void GraphicsButtonObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setPixmap(m_releasedGfx);
    emit clicked();
}

void GraphicsButtonObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setPixmap(m_pressedGfx);
}

