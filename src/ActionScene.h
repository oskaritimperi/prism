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

class QGraphicsPixmapItem;
class Hero;

class ActionScene : public GameScene
{
    Q_OBJECT

public:
    explicit ActionScene(const QString &name, const QRectF &rect, GameView *parent = 0);
    virtual ~ActionScene();

    void updateLogic();
    void keyPressEvent(QKeyEvent *event);

    /**
      * Loads level from target location.
      */
    void loadMap(QString target);

private:

    Tiled::Map *m_map;
    Tiled::MapReader *m_mapReader;
    Tiled::OrthogonalRenderer *m_mapRenderer;

    //! Level name used for records.
    QString m_levelName;

    //! Levelscore used for records.
    int m_levelScore;

    //! Map layer is drawn to this pixmap
    QPixmap m_mapPixmap;

    //! Item for map layer
    QGraphicsPixmapItem *m_mapPixmapItem;

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

    //! HP text item
    QGraphicsTextItem* m_hpText;
    //! Score text item
    QGraphicsTextItem* m_scoreText;

signals:
    void gameOver();

public slots:
    /**
   * Removes a sprite from the scene
   */
    void removeSprite();
};

#endif // ActionScene_H
