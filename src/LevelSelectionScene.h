#ifndef LevelSelectionScene_h
#define LevelSelectionScene_h

#include "GameScene.h"

#include "ParallaxScrollerStatic.h"

class LevelSelectionScene : public GameScene
{
    Q_OBJECT
public:
    LevelSelectionScene(const QString &name, const QRectF &rect, GameView *parent = 0);
    virtual ~LevelSelectionScene();

    /**
      * Updates graphics on scene. Mainly background but levelselectionbuttons too.
      */
    void updateLogic();

    /**
      * Loads level data and creates selection grid
      */
    void initializeScene();

private slots:
    /**
      * This function calls ActionScene with information about what level to load.
      */
    void levelSelection();

private:
    ParallaxScrollerStatic* m_background;

};

#endif // LevelSelectionScene_h
