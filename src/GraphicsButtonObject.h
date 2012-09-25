#ifndef GraphicsButtonObject_h
#define GraphicsButtonObject_h

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsLayoutItem>
#include <QPixmap>

/**
  * Used for creating nice buttons to menus.
  */
class GraphicsButtonObject :
        public QObject,
        public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit GraphicsButtonObject(const QPixmap &releasedPixmap,
                                  QGraphicsPixmapItem *parent = 0,
                                  QGraphicsScene *scene = 0);

    explicit GraphicsButtonObject(QGraphicsPixmapItem *parent = 0,
                                  QGraphicsScene *scene = 0);

    GraphicsButtonObject(const QString &str,
                         QGraphicsPixmapItem *parent = 0,
                         QGraphicsScene *scene = 0);

    ~GraphicsButtonObject();

    /**
      * Sets gfx to indicate pressed-state on button.
      * @param &pixmap The pixmap used as gfx
      */
    void setPressedPixmap(const QPixmap &pixmap);

    /**
      * Sets gfx to indicate released/normal-state on button.
      * @param &pixmap The pixmap used as gfx
      */
    void setReleasedPixmap(const QPixmap &pixmap);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QPixmap m_pressedGfx;
    QPixmap m_releasedGfx;

    static QPixmap *s_tmpGfx;
    static int s_ref;

signals:
    void clicked();
};

#endif // GraphicsButtonObject_h
