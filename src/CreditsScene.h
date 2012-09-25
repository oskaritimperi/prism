#ifndef CreditsScene_h
#define CreditsScene_h

#include "GameScene.h"

#include "ParallaxScrollerStatic.h"

class CreditsScene : public GameScene
{
public:
    CreditsScene(const QString &name, const QRectF &rect, GameView *parent = 0);
    virtual ~CreditsScene();

    void updateLogic();

    /**
      * Initializes resources used on scene.
      */
    void initializeScene();

private:
    ParallaxScrollerStatic* m_background;
};

#endif // CreditsScene_h
