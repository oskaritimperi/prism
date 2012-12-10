#ifndef Hero_h
#define Hero_h

#include "Character.h"

class b2World;
class b2Body;
class b2Fixture;

class Hero: public Character
{
    Q_OBJECT

public:
    Hero(QGraphicsScene* scene, QPointF pos, QGraphicsItem* parent = 0);
    virtual ~Hero();

    void bindToWorld(b2World* world);

    void loadAnimations(const QString& animationsDirectory);

    void advance(int phase);

    /**
      * Update the position of the ball. x and y are in pixels.
      */
    void updatePosition(qreal x, qreal y);

    /**
      * Returns the Box2D fixture for the ball.
      */
    b2Fixture *getFixture();

    void toggleRedColor();
    void toggleGreenColor();
    void toggleBlueColor();

signals:
    void gameOver();
    void levelComplete();
    void updateUI();

private:
    QPixmap* m_red;
    QPixmap* m_green;
    QPixmap* m_blue;
    QPixmap* m_neutral;
    QString m_mode;

    b2Body* m_body;
    b2Fixture *m_fixture;
};

#endif // Hero_h
