#include <QApplication>

#include "ParallaxScrollerStatic.h"
#include "GraphicsButtonObject.h"
#include "GameView.h"

#include "MenuScene.h"

MenuScene::MenuScene(const QString &name, const QRectF &rect, GameView *parent)
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

MenuScene::~MenuScene()
{
    delete m_background;
}

void MenuScene::updateLogic()
{
    advance();
    update();
}

void MenuScene::initializeScene()
{
    int yoff = 200;

    GraphicsButtonObject *btn1 = new GraphicsButtonObject("Play", 0, this);
    btn1->setPos(260, yoff);

    GraphicsButtonObject *btn2 = new GraphicsButtonObject("Credits", 0, this);
    btn2->setPos(260, btn1->pos().y() + btn1->boundingRect().bottom() + 20);

    GraphicsButtonObject *btn3 = new GraphicsButtonObject("Quit", 0, this);
    btn3->setPos(260, btn2->pos().y() + btn2->boundingRect().bottom() + 20);

    connect(btn1, SIGNAL(clicked()), gameView(), SLOT(showLevelSelectionScene()));
    connect(btn2, SIGNAL(clicked()), gameView(), SLOT(showCreditsScene()));
    connect(btn3, SIGNAL(clicked()), qApp, SLOT(quit()));

    addTitle("prism");
}
