#include "Sprite.h"

Sprite::Sprite(QGraphicsItem *parent, QGraphicsScene *scene)
	: QObject(0),
	  QGraphicsPixmapItem(parent, scene),
	  m_currentFrame(0),
      m_interval(1000/20)
{
    addAnimation("default", FrameList());
    setAnimation("default");

    m_timer.invalidate();
}

void Sprite::addFrame(const QString &anim, QPixmap frame)
{
    if (!m_animations.contains(anim))
    {
        FrameList l;
        m_animations[anim] = l;
    }

    m_animations[anim].append(frame);
}

void Sprite::addAnimation(const QString &anim, const FrameList &frames)
{
    if (!m_animations.contains(anim))
    {
        m_animations[anim] = frames;
    }
    else
    {
        m_animations[anim].append(frames);
    }
}

void Sprite::setFrame(int frame)
{
    if (frame < 0 || frame >= getCurrentAnimation().size())
    {
        qWarning("invalid frame number %d", frame);
        return;
    }

    m_currentFrame = frame;
    setPixmap(getFramePixmap());
}

int Sprite::getFrame() const
{
    return m_currentFrame;
}

QPixmap Sprite::getFramePixmap() const
{
    return getCurrentAnimation()[m_currentFrame];
}

int Sprite::getFrameCount() const
{
    return getCurrentAnimation().size();
}

Sprite::FrameList Sprite::getCurrentAnimation() const
{
    return m_animations[m_currentAnimation];
}

void Sprite::nextFrame()
{
    m_currentFrame++;

    if (m_currentFrame >= getCurrentAnimation().size())
        m_currentFrame = 0;

    setFrame(m_currentFrame);
}

void Sprite::setAnimation(const QString &anim)
{
    if (!m_animations.contains(anim))
    {
        qWarning("animation '%s' doesn't exist", anim.toUtf8().data());
        return;
    }

    if (m_currentAnimation != anim)
        m_currentAnimation = anim;
}

void Sprite::advance(int phase)
{
    if (phase == 1)
        return;

    if (m_timer.isValid() && m_timer.elapsed() >= m_interval)
    {
        nextFrame();
        m_timer.start();
    }

    // this should be run the first time advance() is called
    if (!m_timer.isValid())
    {
        m_timer.start();
    }
}
