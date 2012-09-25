#ifndef GameScene_h
#define GameScene_h

#include <QGraphicsScene>

class GameView;

//! Used in QGraphicsItem::setData()/data()
static const int ITEM_OBJECTNAME = 0;


/**
  * The base class for all scenes in the game. GameScene class offers some
  * convenience methods for all its children. This also helps the management
  * of the scenes in GameView.
  */
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(const QString &name, GameView *parent = 0);

    /**
      * This should be called when the scene is entered, i.e. the scene
      * becomes the active scene.
      */
    virtual void enterScene(GameScene *prev = 0);

    /**
      * This should be called when the scene is losing its active status.
      */
    virtual void leaveScene(GameScene *next = 0);

    /**
      * Used for updating contents of scene.
      */
    virtual void updateLogic() = 0;

    /**
      * Convenience method to get the associated GameView instance.
      */
    GameView* gameView() const;

    QGraphicsPixmapItem *addTitle(const QString &title, int pointSize = 75);

protected:
    GameView* m_gameView;

signals:

public slots:

};

#endif // GameScene_h
