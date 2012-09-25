#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QDebug>

#include "GameView.h"

#include "GameScene.h"

GameScene::GameScene(const QString &name, GameView *parent) :
    QGraphicsScene(parent)
{
    setObjectName(name);
    m_gameView = parent;
}

GameView* GameScene::gameView() const
{
    return m_gameView;
}

void GameScene::enterScene(GameScene *)
{
    qDebug() << __FUNCTION__ << objectName();
}

void GameScene::leaveScene(GameScene *)
{
    qDebug() << __FUNCTION__ << objectName();
}

QGraphicsPixmapItem* GameScene::addTitle(const QString &title, int pointSize)
{
    //    // Draw text with a black outline and using a gradient as a brush :-)
    QLinearGradient grad;

    grad.setCoordinateMode(QGradient::ObjectBoundingMode);

    grad.setStart(0, 0);
    grad.setFinalStop(0, 1);

    /* the old gradient
    grad.setColorAt(0, Qt::white);
    grad.setColorAt(0.25, QColor(226, 174, 31));
    grad.setColorAt(0.5, QColor(149, 113, 16));
    grad.setColorAt(0.51, Qt::white);
    grad.setColorAt(1, QColor(68, 153, 213));
    */

    grad.setColorAt(0, Qt::white);
    grad.setColorAt(0.20, QColor(137, 175, 201));
    grad.setColorAt(0.35, QColor(35, 136, 207));
    grad.setColorAt(0.5, QColor(32, 98, 145));
    grad.setColorAt(0.65, QColor(35, 136, 207));
    grad.setColorAt(0.80, QColor(137, 175, 201));
    grad.setColorAt(1, Qt::white);

    QFont font("Arial", pointSize);
    font.setUnderline(true);
    font.setLetterSpacing(QFont::PercentageSpacing, 95);
    font.setWordSpacing(-20);

    QFontMetrics metrics(font);
//    QRect bbox = metrics.boundingRect(title);

//    qDebug() << metrics.boundingRect("MAZENNUS");
//    qDebug() << metrics.width("MAZENNUS") << metrics.height();

    QPainterPath path;
    //    path.addText(pixmap.width()/2-bbox.width()/2, 20+metrics.ascent(), font, "MAZENNUS");
    path.addText(0, metrics.ascent(), font, title);

    QImage img(metrics.width(title), metrics.height()+3, QImage::Format_ARGB32);

    QPainter painter(&img);

    // set dst pixels to transparent regardless of src
    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    painter.fillRect(img.rect(), Qt::white);

    // switch back to normal
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 3));
    painter.setBrush(grad);

    painter.drawPath(path);

    QPixmap pixmap = QPixmap::fromImage(img);

    QGraphicsPixmapItem *i = addPixmap(pixmap);

    i->setPos(sceneRect().width()/2 - pixmap.width()/2, 20);

    return i;
}
