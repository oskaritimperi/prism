#ifndef GameView_h
#define GameView_h

#include <QGraphicsView>
#include <QList>
#include <QTimer>

class ActionScene;
class GameScene;
class SceneChanger;

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    static GameView *instance();

    GameScene *getScene(const QString &);
    GameScene *getCurrentScene();

    ActionScene* getActionScene();

signals:

public slots:

    void gameOver();

    void showMenuScene();
    void showLevelSelectionScene();
    void showCreditsScene();
    void showActionScene();

    void changeScene(GameScene* );
    void showScene(GameScene *);
    void showScene(const QString &);

private slots:

    //! Calls GameScene::updateLogic of the current scene
    void updateSceneLogic();

private:
    explicit GameView(QWidget *parent = 0);

    static GameView *m_instance;

    ActionScene* m_actionScene;
    SceneChanger* m_sceneChanger;

    QList<GameScene *> m_scenes;

    //! Timer used to scene updates
    QTimer *m_gameTimer;
};

#endif // GameView_h
