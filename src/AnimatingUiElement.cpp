#include <QPropertyAnimation>
#include <QLinearGradient>
#include <QPainter>
#include <QDebug>

#include "AnimatingUiElement.h"

QPixmap* AnimatingUiElement::s_tmpGfx = 0;
int AnimatingUiElement::s_ref = 0;

AnimatingUiElement::AnimatingUiElement(const QString& text, QObject *parent, QGraphicsItem* graphicsParent) :
    QObject(parent), QGraphicsPixmapItem(graphicsParent)
{
    m_durationPressed = 500;
    m_durationReleased = 400;
    m_text = text;

    m_animation = 0;

    initialize();
}

AnimatingUiElement::~AnimatingUiElement()
{
    s_ref--;

    if (s_tmpGfx && s_ref == 0)
    {
        delete s_tmpGfx;
        s_tmpGfx = 0;
    }
}

void AnimatingUiElement::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_animation)
    {
        m_animation->stop();
        delete m_animation;
        m_animation = 0;
    }

    m_animation = new QPropertyAnimation(this, "scale");
    connect(m_animation, SIGNAL(finished()), this, SLOT(animationFinished()));
    m_animation->setDuration(m_durationPressed);
    m_animation->setEndValue(1.3);
    m_animation->setEasingCurve(QEasingCurve::OutBounce); //or OutBounce, OutQuint...

    m_animation->start();

    m_released = false;
}

void AnimatingUiElement::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_released = true;

    if (m_animation)
    {
        m_animation->stop();
        delete m_animation;
        m_animation = 0;
    }

    m_animation = new QPropertyAnimation(this, "scale");
    connect(m_animation, SIGNAL(finished()), this, SLOT(animationFinished()));
    m_animation->setDuration(m_durationReleased);
    m_animation->setEndValue(1.0);
    m_animation->setEasingCurve(QEasingCurve::OutBounce); //or OutBounce, OutQuint...

    m_animation->start();

    m_released = true;
}

void AnimatingUiElement::initialize()
{
    s_ref++;

    int pw = 280;
    int ph = 60;

    // Draw the gradients only once
    if (!s_tmpGfx)
    {
        //DBG("generating button gradients");

        s_tmpGfx = new QPixmap(pw, ph);
        QPainter painter(s_tmpGfx);

        painter.setPen(Qt::NoPen);

        painter.setBrush(Qt::white);
        painter.drawRect(s_tmpGfx->rect());

        QLinearGradient grad;

        grad.setCoordinateMode(QGradient::ObjectBoundingMode);

        grad.setStart(0, 0);
        grad.setFinalStop(0, 1);

        grad.setColorAt(0, Qt::red);
        grad.setColorAt(0.20, QColor(255, 127, 0));
        grad.setColorAt(0.35, QColor(255, 255, 0));
        grad.setColorAt(0.5, QColor(0, 255, 0));
        grad.setColorAt(0.65, QColor(0, 0, 255));
        grad.setColorAt(0.80, QColor(111, 0, 255));
        grad.setColorAt(1, QColor(143, 0, 255));

        painter.setBrush(QBrush(grad));
        painter.drawRect(4, 4, pw-8, ph-8);
    }

    QPixmap buttonImage = QPixmap(*s_tmpGfx);
    QPainter painter(&buttonImage);

    QFont font("Arial", 36);
    font.setLetterSpacing(QFont::PercentageSpacing, 95);

    QFontMetrics metrics(font);
    QRect bbox = metrics.boundingRect(m_text);

    QPainterPath path;

    int x = (ph - metrics.height()) / 2;
    path.addText(pw/2-bbox.width()/2, x + metrics.ascent(),  font, m_text);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 3));
    painter.setBrush(Qt::white);
    painter.drawPath(path);

    setPixmap(buttonImage);
}

void AnimatingUiElement::animationFinished()
{
    delete m_animation;
    m_animation = 0;
    if (m_released)
    {
        m_released = false;
        emit clicked();
    }
}
