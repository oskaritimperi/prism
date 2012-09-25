#include <QApplication>
#include <QDir>
#include <QSettings>
#include <QDebug>

#include "ParallaxScrollerStatic.h"
#include "GraphicsButtonObject.h"
#include "GameView.h"
#include "ActionScene.h"

#include "LevelSelectionScene.h"

LevelSelectionScene::LevelSelectionScene(const QString &name, const QRectF &rect, GameView *parent)
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

LevelSelectionScene::~LevelSelectionScene()
{
    delete m_background;
}

void LevelSelectionScene::initializeScene()
{
    addTitle("Level Selection");

    QSettings settings;

    QDir levelDirectory(settings.value("path/levels").toString());

    /* TODO: check levels directory for levels (should be 6) and create corresponding buttons
             that react when pressed and lauch the level
             */
    int yoff = 200;
    int xoff = 50;
    int count = 1;

    Q_FOREACH(QString f, levelDirectory.entryList(QDir::Files, QDir::Name))
    {
        QString lvlNum;
        lvlNum.setNum(count);
        GraphicsButtonObject *btn = new GraphicsButtonObject(lvlNum, 0, this);
		btn->setPos(210 + xoff, yoff);
        btn->setProperty("level_path", levelDirectory.filePath(f));

        qDebug() << levelDirectory.filePath(f);

        connect(btn, SIGNAL(clicked()), this, SLOT(levelSelection()));

//        if(count % 4 == 0)
//        {
//            yoff += btn->boundingRect().bottom() + 20;
//            xoff = 50;
//        }

        count++;
		//xoff += btn->boundingRect().bottom() + 20;
		yoff += btn->boundingRect().bottom() + 10;
    }

    GraphicsButtonObject *btn;
    btn = new GraphicsButtonObject(QPixmap(QApplication::applicationDirPath() + "/gfx/buttons/back-arrow1.png"), 0, this);
    btn->setPressedPixmap(QPixmap(QApplication::applicationDirPath() + "/gfx/buttons/back-arrow2.png"));
    btn->setPos(720, 400);
    btn->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    btn->setZValue(2);

    connect(btn, SIGNAL(clicked()), gameView(), SLOT(showMenuScene()));
}

void LevelSelectionScene::levelSelection()
{
    QVariant level_path = sender()->property("level_path");

    Q_ASSERT(level_path.isValid());

    QString levelPath = level_path.toString();

    gameView()->getActionScene()->loadMap(levelPath);
    gameView()->showActionScene();
}

void LevelSelectionScene::updateLogic()
{
    advance();
    update();
}

