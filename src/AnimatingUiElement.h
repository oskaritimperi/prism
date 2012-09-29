#ifndef AnimatingUiElement_h
#define AnimatingUiElement_h

#include <QObject>
#include <QGraphicsPixmapItem>

class QPropertyAnimation;

class AnimatingUiElement : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    Q_PROPERTY(qreal scale READ scale WRITE setScale)
public:
    AnimatingUiElement(const QString& text, QObject *parent = 0, QGraphicsItem* graphicsParent = 0);
    virtual ~AnimatingUiElement();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void initialize();

signals:
    void clicked();

public slots:

private slots:
    void animationFinished();

private:
    QPropertyAnimation* m_animation;
    QString m_text;
    bool m_released;
    int m_durationPressed;
    int m_durationReleased;

    static QPixmap *s_tmpGfx;
    static int s_ref;
};

#endif // AnimatingUiElement_h
