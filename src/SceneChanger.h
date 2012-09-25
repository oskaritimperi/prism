#ifndef SceneChanger_h
#define SceneChanger_h

#include "GameScene.h"

class QParallelAnimationGroup;
class QTimer;
class GameView;

/**
  * Animates the change from a scene to another. Start the change
  * with SceneChanger::changeScene(). After the animation is done,
  * SceneChanger calls MainView::showScene for the scene that is
  * to be shown.
  *
  * Basically changeScene() just takes a "screenshot" of both the
  * scenes, adds the shots to itself and uses QPropertyAnimation
  * to do the animation.
  */
class SceneChanger : public GameScene
{
    Q_OBJECT
public:
    explicit SceneChanger(QString name, const QRectF &rect, GameView *parent = 0);

    /**
      * Start the scene change animation.
      *
      * @param from The scene we are changing from
      * @param to The scene we are changing to
      */
    void changeScene(GameScene *from, GameScene *to, bool rightToLeft);

    /**
      * Sets the duration of the animation in milliseconds. Default
      * duration is 250 milliseconds.
      */
    void setDuration(int msecs);

    void updateLogic();

private:

    /**
      * Center of all the animation.
      */
    QParallelAnimationGroup *m_anim;

    GameScene *m_fromScene;
    GameScene *m_toScene;

    /**
      * Time in ms how long it takes to animate from view to an other.
      */
    int m_duration;

    /**
      * Used for faster update on animating transition
      * than normal rendering needs.
      */
    QTimer *m_updateTimer;

signals:

private slots:
    /**
      * Called after m_anim has finished the animation. Calls
      * MainView::showScene() to show the new scene.
      */
    void animationFinished();

};

#endif // SceneChanger_h
