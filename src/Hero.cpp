#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QSettings>
#include <QPainter>
#include <QDir>
#include <QColor>
#include <QDebug>

#include "Box2D/Dynamics/b2World.h"
#include "Box2d/Dynamics/b2Body.h"
#include "Box2d/Dynamics/b2Fixture.h"
#include "Box2d/Collision/Shapes/b2PolygonShape.h"

#include "common.h"

#include "Hero.h"
#include "GameScene.h"

Hero::Hero(QGraphicsScene* scene, QPointF pos, QGraphicsItem* parent)
    : Character(parent, scene)
{
    m_state = STATE_IDLE;

    // something small for testing purposes
    setHealthPoints(15);

    setPos(pos);
    setZValue(2);

    setShapeMode(QGraphicsPixmapItem::MaskShape);

    m_mode = "neutral";

    m_neutral = new QPixmap(32, 64);
    m_neutral->fill(Qt::transparent);
    setPixmap(*m_neutral);

    m_red = new QPixmap(32, 64);
    m_red->fill(Qt::transparent);
    QPainter p;
    p.setPen(Qt::NoPen);
    QBrush b(Qt::transparent);
    p.begin(m_red);
    b.setColor(QColor(127, 0, 0, 127));
    p.setBrush(b);
    p.drawRoundedRect(QRect(0, 0, 31, 63), 5, 5);
    p.end();

    m_green = new QPixmap(32, 64);
    m_green->fill(Qt::transparent);
    p.begin(m_green);
    b.setColor(QColor(0, 127, 0, 127));
    p.setBrush(b);
    p.drawRoundedRect(QRect(0, 0, 31, 63), 5, 5);
    p.end();

    m_blue = new QPixmap(32, 64);
    m_blue->fill(Qt::transparent);
    p.begin(m_blue);
    b.setColor(QColor(0, 0, 127, 127));
    p.setBrush(b);
    p.drawRoundedRect(QRect(0, 0, 31, 63), 5, 5);
    p.end();
}

Hero::~Hero()
{
    if (m_red)
        delete m_red;
    if (m_green)
        delete m_green;
    if (m_blue)
        delete m_blue;
    if (m_neutral)
        delete m_neutral;
}

void Hero::bindToWorld(b2World *world)
{
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(P2M(16), P2M(32));

    m_body = world->CreateBody(&bd);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(P2M(32.0f / 2),
                          P2M(64.0f / 2),
                          b2Vec2(P2M(32.0f / 2),
                                 P2M(64.0f / 2)),
                          0.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = 15;
    fixtureDef.friction = 0.05f;
    fixtureDef.restitution = 0.25f;
    fixtureDef.userData = this;

    m_fixture = m_body->CreateFixture(&fixtureDef);

    b2MassData md;
    m_body->GetMassData(&md);
    md.mass = 0.7f;
    m_fixture->GetBody()->SetMassData(&md);

    qDebug() << "mass: " << m_body->GetMass() << "kg";
}

void Hero::loadAnimations(const QString &animationsDirectory)
{
    QDir animDirs(animationsDirectory);

    foreach(QString animName, animDirs.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QDir anim(animationsDirectory + "/" + animName);

        foreach(QString frame, anim.entryList(QDir::Files | QDir::NoDotAndDotDot))
        {
            addFrame(animName, QPixmap(animationsDirectory + "/" + animName + "/" + frame));
        }
    }
    setAnimation("idle");
}

void Hero::advance(int phase)
{
    Character::advance(phase);

    if (phase == 0)
    {
        return;
    }
    else if (phase == 1)
    {
        b2Vec2 pos = m_body->GetPosition();
        setPos(M2P(pos.x)-16, M2P(pos.y)-32);
    }

    // err, no good.
    if(m_state == STATE_DEAD)
    {
        gameOver();
        //removeMe();
    }
}

void Hero::updatePosition(qreal x, qreal y)
{
    m_body->SetTransform(b2Vec2(P2M(x), P2M(y)), 0);
    setPos(x-16, y-32);
}

void Hero::toggleRedColor()
{
    if (m_mode == "neutral")
    {
        setPixmap(*m_red);
        m_mode = "red";
    }
    else if (m_mode == "red")
    {
        setPixmap(*m_neutral);
        m_mode = "neutral";
    }
}

void Hero::toggleGreenColor()
{
    if (m_mode == "neutral")
    {
        setPixmap(*m_green);
        m_mode = "green";
    }
    else if (m_mode == "green")
    {
        setPixmap(*m_neutral);
        m_mode = "neutral";
    }
}

void Hero::toggleBlueColor()
{
    if (m_mode == "neutral")
    {
        setPixmap(*m_blue);
        m_mode = "blue";
    }
    else if (m_mode == "blue")
    {
        setPixmap(*m_neutral);
        m_mode = "neutral";
    }
}


b2Fixture* Hero::getFixture()
{
    return m_fixture;
}
