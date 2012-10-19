#ifndef ActionScene_H
#define ActionScene_H

#include <QObject>
#include <QRectF>
#include <QGraphicsRectItem>

#include "GameScene.h"
#include "Sprite.h"

#include "map.h"
#include "mapreader.h"
#include "orthogonalrenderer.h"

#include "Box2D.h"

class QGraphicsPixmapItem;
class Hero;
class HeadsUpDisplay;

class b2World;

class ActionScene : public GameScene
{
    Q_OBJECT

public:
    explicit ActionScene(const QString &name, const QRectF &rect, GameView *parent = 0);
    virtual ~ActionScene();

    void updateLogic();
    void keyPressEvent(QKeyEvent *event);

    /**
      * TODO: Bind in-game background parallax-scroller to this
      */
    void drawBackground(QPainter *painter, const QRectF &rect);

    /**
      * Used to draw HUD, TODO: implementation
      */
    void drawForeground(QPainter *painter, const QRectF &rect);

    /**
      * Loads level from target location.
      */
    void loadMap(QString target);

    /**
      * Unloads map, releasing its resources from memory
      */
    void unloadMap();

private:

    b2World* m_physicalWorld;

    Tiled::Map *m_map;
    Tiled::MapReader *m_mapReader;
    Tiled::OrthogonalRenderer *m_mapRenderer;

    //! Level name used for records.
    QString m_levelName;

    //! Levelscore used for records.
    int m_levelScore;

    //! Map layers are drawn to these pixmaps
    QVector<QPixmap> m_mapPixmaps;

    //! Items for map layers
    QVector<QGraphicsPixmapItem*> m_mapPixmapItems;

    //! What portion of the map to draw
    QSize m_mapWindow;

    //! Background pixmap
    QPixmap m_bgPixmap;
    QGraphicsPixmapItem *m_bgPixmapItem;

    //! What portion of the bg pixmap to draw
    QRectF m_bgWindow;

    //! Pointer for forwarding commands to main character
    Hero* m_hero;

    //! Stops graphics rendering while scene is cleared.
    bool m_clearAlert;

    //! This item contais all hud elements, rendered in drawForeground
    HeadsUpDisplay* m_hud;

signals:
    void gameOver();

public slots:
    /**
   * Removes a sprite from the scene
   */
    void removeSprite();
};

#endif // ActionScene_H
