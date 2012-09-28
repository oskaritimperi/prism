#include <QApplication>
#include <QGraphicsTextItem>

#include <QDebug>

#include "GameView.h"
#include "GraphicsButtonObject.h"
#include "ParallaxScrollerStatic.h"

#include "CreditsScene.h"

CreditsScene::CreditsScene(const QString &name, const QRectF &rect, GameView *parent)
    : GameScene(name, parent)
{
    setSceneRect(rect);

    QString appDir = qApp->applicationDirPath();

    m_background = new ParallaxScrollerStatic(this);
    m_background->setLayerWidth(rect.width());
    //m_background->addParallaxScrollItem(QString(appDir + "/gfx/bg/layer1.png"), QPointF(0,0), -2, 6);
    //m_background->addParallaxScrollItem(QString(appDir + "/gfx/bg/layer2.png"), QPointF(0,0), -1, 4);

    m_background->addParallaxScrollItem(QString(appDir + "/data/gfx/background/layer_three.png"), QPointF(0,0), -3, 8);
    m_background->addParallaxScrollItem(QString(appDir + "/data/gfx/background/layer_two.png"), QPointF(0,0), -2, 6);
    m_background->addParallaxScrollItem(QString(appDir + "/data/gfx/background/layer_one.png"), QPointF(0,0), -1, 4);

    initializeScene();
}

CreditsScene::~CreditsScene()
{
    delete m_background;
}

void CreditsScene::initializeScene()
{
    addTitle("Credits");

    QGraphicsTextItem* creditText = new QGraphicsTextItem(0, this);
    creditText->setHtml("<font color=\"white\">"\
                        "<b>prism</b> (v. 0.0.3) <br><br>"\
                        "Game design,<br>"\
                        "concept design and<br>"\
                        "programming by:<br>"\
                        "Samu Laaksonen<br>"\
                        "and <br>"\
                        "Oskari Timperi<br><br>"\
                        "Copyright (c) 2012 of aforementioned persons. All rights reserved.<br>"\
                        "</font>");
    creditText->setPos(140, 130);
    creditText->setFont(QFont("Arial", 14));

    GraphicsButtonObject *btn;
    btn = new GraphicsButtonObject(QPixmap(qApp->applicationDirPath() + "/data/gfx/buttons/back-arrow1.png"),
                                   0, this);
    btn->setPressedPixmap(QPixmap(qApp->applicationDirPath() + "/data/gfx/buttons/back-arrow2.png"));
    btn->setPos(720, 400);
    btn->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    btn->setZValue(2);

    connect(btn, SIGNAL(clicked()), gameView(), SLOT(showMenuScene()));
}

void CreditsScene::updateLogic()
{
    advance();
    update();
}
