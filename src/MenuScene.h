#ifndef MenuScene_h
#define MenuScene_h

#include "GameScene.h"

#include "ParallaxScrollerStatic.h"

class GameView;

/**
  * Scene for first view displayed when application launches.
  */
class MenuScene : public GameScene
{
    Q_OBJECT
public:
    MenuScene(const QString &name, const QRectF &rect, GameView *parent = 0);
    virtual ~MenuScene();

    void initializeScene();

    void updateLogic();

signals:

public slots:

private:
    ParallaxScrollerStatic* m_background;
};

#endif // MenuScene_h
