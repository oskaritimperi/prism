#ifndef SPRITE_H
#define SPRITE_H

#include <QList>
#include <QMap>
#include <QString>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QElapsedTimer>
#include <QObject>

class Sprite: public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:
    typedef QList<QPixmap> FrameList;

    explicit Sprite(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    //! Adds a frame to an animation
    void addFrame(const QString &anim, QPixmap frame);

    //! Adds a list of frames to an animation
    void addAnimation(const QString &anim, const FrameList &frames);

    //! Set current frame in the current animation
    void setFrame(int frame);

    //! Get current frame
    int getFrame() const;

    //! Change to next frame
    void nextFrame();

    QPixmap getFramePixmap() const;

    //! Get frame count in current animation
    int getFrameCount() const;

    FrameList getCurrentAnimation() const;

    void setAnimation(const QString &anim);

    void setFrameInterval(int msecs) { m_interval = msecs; }
    int frameInterval() const { return m_interval; }

    virtual void advance(int phase);

signals:
    //! Marks this sprite for removal
    void removeMe();

protected:

    //! Map of animations (i.e. running, idle, jumping, ...)
    QMap<QString, FrameList> m_animations;

    QString m_currentAnimation;

    //! Current frame
    int m_currentFrame;

    //! How often frames should be changed
    int m_interval;

    QElapsedTimer m_timer;
};

#endif // SPRITE_H
