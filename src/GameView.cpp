#include <QScrollBar>
#include <QDebug>
#include <QtOpenGL/QGLWidget>

#include "ActionScene.h"
#include "LevelSelectionScene.h"
#include "CreditsScene.h"
#include "SceneChanger.h"
#include "MenuScene.h"

#include "GameView.h"

GameView *GameView::m_instance = NULL;

GameView::GameView(QWidget *parent) :
    QGraphicsView(parent)
{
    setViewport(new QGLWidget);

    m_actionScene = new ActionScene("ActionScene", QRectF(0, 0, 6400, 480), this);
    connect(m_actionScene, SIGNAL(gameOver()), this, SLOT(gameOver()));

    LevelSelectionScene* levelSelectionScene = new LevelSelectionScene("LevelSelectionScene", QRectF(0, 0, 800, 480), this);
    CreditsScene* creditsScene = new CreditsScene("CreditsScene", QRectF(0, 0, 800, 480), this);
    MenuScene* menuScene = new MenuScene("MenuScene", QRectF(0, 0, 800, 480), this);

    m_scenes.append(m_actionScene);
    m_scenes.append(levelSelectionScene);
    m_scenes.append(creditsScene);
    m_scenes.append(menuScene);

    m_sceneChanger = new SceneChanger("ChangerScene", QRectF(0, 0, 800, 480), this);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setViewportUpdateMode(FullViewportUpdate);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);

    m_gameTimer = new QTimer(this);
    connect(m_gameTimer, SIGNAL(timeout()), this, SLOT(updateSceneLogic()));

    showScene(menuScene);
}

GameView *GameView::instance()
{
    if (m_instance == NULL)
    {
        m_instance = new GameView;
    }

    return m_instance;
}

GameScene *GameView::getScene(const QString &name)
{
    Q_FOREACH(GameScene *scene, m_scenes)
    {
        if (scene->objectName() == name)
        {
            return scene;
        }
    }

    qDebug() << "GameScene" << name << "not found";

    return NULL;
}

GameScene *GameView::getCurrentScene()
{
    return qobject_cast<GameScene *>(scene());
}

void GameView::showScene(const QString &name)
{
    GameScene *scene = NULL;

    Q_FOREACH(GameScene *s, m_scenes)
    {
        if (s->objectName() == name)
        {
            scene = s;
            break;
        }
    }

    if (scene)
    {
        changeScene(scene);
    }
    else
    {
        qDebug() << "no such scene:" << name;
    }
}

void GameView::changeScene(GameScene* scene)
{
    GameScene *current = getCurrentScene();
    showScene(m_sceneChanger);

    if( current->objectName() == "CreditsScene" && scene->objectName() == "MenuScene" )
           m_sceneChanger->changeScene(current, scene, true);
    else if( current->objectName() == "MenuScene" && scene->objectName() == "LevelSelectionScene" )
        m_sceneChanger->changeScene(current, scene, true);
    else if( current->objectName() == "LevelSelectionScene" && scene->objectName() == "ActionScene" )
        m_sceneChanger->changeScene(current, scene, true);
    else
        m_sceneChanger->changeScene(current, scene, false);
}

void GameView::showScene(GameScene *scene)
{
    Q_ASSERT(scene != NULL);

    GameScene *old = getCurrentScene();

    if (scene == old)
        return;

    m_gameTimer->stop();

    if (old)
        old->leaveScene(scene);

    setScene(scene);

    scene->enterScene(old);

    m_gameTimer->start(1000.0f / 60.0f);
}

void GameView::updateSceneLogic()
{
    GameScene *scene = getCurrentScene();

    if (scene)
    {
        scene->updateLogic();
    }
}

ActionScene* GameView::getActionScene()
{
    return m_actionScene;
}

void GameView::gameOver()
{
    qDebug() << __FUNCTION__;
    // not so simple, man
    showScene("LevelSelectionScene");
}

void GameView::showMenuScene()
{
    showScene("MenuScene");
}

void GameView::showLevelSelectionScene()
{
    showScene("LevelSelectionScene");
}

void GameView::showCreditsScene()
{
    showScene("CreditsScene");
}

void GameView::showActionScene()
{
    showScene("ActionScene");
}
