#include "SceneChanger.h"
#include "GameScene.h"
#include "GameView.h"
#include "GraphicsPixmapObject.h"

#include <QTimer>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

SceneChanger::SceneChanger(QString name,  const QRectF &rect, GameView *parent) :
    GameScene(name, parent)
{
    setSceneRect(rect);

    m_anim = new QParallelAnimationGroup(this);
    connect(m_anim, SIGNAL(finished()), this, SLOT(animationFinished()));
    setDuration(500);

    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(update()));
}

void SceneChanger::updateLogic()
{
    advance();
    update();
}

void SceneChanger::setDuration(int msecs)
{
    m_duration = msecs;
}

void SceneChanger::changeScene(GameScene *from, GameScene *to, bool rightToLeft)
{
    m_fromScene = from;
    m_toScene = to;

    int width = from->sceneRect().width();
    int height = from->sceneRect().height();

    clear();
    m_anim->clear();

    QPixmap from_pixmap(width, height);
    QPixmap to_pixmap(width, height);

    QPainter from_painter(&from_pixmap);
    QPainter to_painter(&to_pixmap);

    from->render(&from_painter);
    to->render(&to_painter);

    GraphicsPixmapObject *from_obj = new GraphicsPixmapObject(from_pixmap);
    from_obj->setPos(0, 0);

    GraphicsPixmapObject *to_obj = new GraphicsPixmapObject(to_pixmap);
    to_obj->setPos(0, 0);

    addItem(from_obj);
    addItem(to_obj);

    QPropertyAnimation *from_anim = new QPropertyAnimation(from_obj, "pos",
                                                           this);

    QPropertyAnimation *to_anim = new QPropertyAnimation(to_obj, "pos",
                                                         this);

    if( rightToLeft )
    {
        from_anim->setDuration(m_duration);
        from_anim->setStartValue(QPointF(0.0, 0.0));
        from_anim->setEndValue(QPointF(-(float)width, 0.0));
        from_anim->setEasingCurve(QEasingCurve::OutCubic); //or OutBounce, OutQuint...

        to_anim->setDuration(m_duration);
        to_anim->setStartValue(QPointF((float)width, 0.0));
        to_anim->setEndValue(QPointF(0.0, 0.0));
        to_anim->setEasingCurve(QEasingCurve::OutCubic); //or OutBounce, OutQuint...
    }
    else
    {
        from_anim->setDuration(m_duration);
        from_anim->setStartValue(QPointF(0.0, 0.0));
        from_anim->setEndValue(QPointF((float)width, 0.0));
        from_anim->setEasingCurve(QEasingCurve::OutCubic); //or OutBounce, OutQuint...

        to_anim->setDuration(m_duration);
        to_anim->setStartValue(QPointF(-(float)width, 0.0));
        to_anim->setEndValue(QPointF(0.0, 0.0));
        to_anim->setEasingCurve(QEasingCurve::OutCubic); //or OutBounce, OutQuint...

    }
    m_anim->addAnimation(from_anim);
    m_anim->addAnimation(to_anim);

    // Use a little more frequent update than normally
    m_updateTimer->start(1000 / 100);
    m_anim->start();
}

void SceneChanger::animationFinished()
{
    m_updateTimer->stop();

    gameView()->showScene(m_toScene);
}
