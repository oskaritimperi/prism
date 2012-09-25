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
    m_background->addParallaxScrollItem(QString(appDir + "/gfx/bg/layer1.png"), QPointF(0,0), -2, 6);
    m_background->addParallaxScrollItem(QString(appDir + "/gfx/bg/layer2.png"), QPointF(0,0), -1, 4);

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
    creditText->setHtml("<b>WalRush</b> (v. 1.0) <br><br>"\
                        "WalRush was originally a project "\
                        "for course in TAMK.<br><br>"\
                        "Programming by:<br>"\
                        "Samu Laaksonen<br>"\
                        "Oskari Timperi<br><br>"\
                        "Graphics by: <br>"\
                        "Lauri Paakinaho<br><br>"\
                        "Copyright (c) 2010 of aforementioned persons. All rights reserved.<br>");
    creditText->setPos(140, 130);
    creditText->setFont(QFont("Arial", 14));

    GraphicsButtonObject *btn;
    btn = new GraphicsButtonObject(QPixmap(qApp->applicationDirPath() + "/gfx/buttons/back-arrow1.png"),
                                   0, this);
    btn->setPressedPixmap(QPixmap(qApp->applicationDirPath() + "/gfx/buttons/back-arrow2.png"));
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
