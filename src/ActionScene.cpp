#include <QPainter>
#include <QPainterPath>
#include <QColor>
#include <QBrush>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

#include <QSettings>

#include <QApplication>
#include <QTime>
#include <QFileInfo>
#include <QMessageBox>

#include "MainWindow.h"
#include "GameView.h"
#include "Hero.h"
#include "ParallaxScrollerStatic.h"
#include "Collectible.h"
#include "HeadsUpDisplay.h"

#include "layer.h"
#include "objectgroup.h"
#include "mapobject.h"
#include "tile.h"
#include "tilelayer.h"

#include "Box2d/Dynamics/b2World.h"
#include "Box2d/Dynamics/b2Fixture.h"
#include "Box2d/Collision/Shapes/b2PolygonShape.h"
#include "Box2d/Collision/Shapes/b2EdgeShape.h"

#include "common.h"

#include "ActionScene.h"

using Tiled::Map;
using Tiled::MapReader;
using Tiled::OrthogonalRenderer;
using Tiled::Layer;
using Tiled::ObjectGroup;
using Tiled::Tile;
using Tiled::TileLayer;

ActionScene::ActionScene(const QString &name, const QRectF &rect, GameView *parent)
    : GameScene(name, parent)
{
    setSceneRect(rect);
    m_clearAlert = false;
    m_mapReader = new Tiled::MapReader;

    m_map = 0;
    m_mapRenderer = 0;

    m_hud = new HeadsUpDisplay(sceneRect().width(), sceneRect().height(), this, this);

    // start setting up the world here
    b2Vec2 gravity(0.0f, 10.0f);
    m_world = new b2World(gravity);
    m_world->SetAllowSleeping(true);

    // initialize rand here
    qsrand(QTime::currentTime().msec());
    // TODO: implement some logic to randomize color bubbles given to player

    QString appDir = qApp->applicationDirPath();

    m_hero = new Hero(this, QPointF(150, 150));
    m_hero->loadAnimations(QString(appDir + "/data/gfx/characters/hero/"));

    //connect(m_hero, SIGNAL(removeMe()), this, SLOT(removeSprite()));
}

ActionScene::~ActionScene()
{
    if (m_map)
        delete m_map;
    if (m_mapReader)
        delete m_mapReader;
    if (m_mapRenderer)
        delete m_mapRenderer;

    if(m_world)
        delete m_world;
}

void ActionScene::updateLogic()
{
    if(!m_clearAlert)
    {
        // Collision logic through sheer awesomeness of Box2D, FTW.
        m_world->Step(1.0f / FPS, 5, 5);
        m_world->ClearForces();

        advance();
        update();
        m_hud->update();
    }
}

void ActionScene::keyPressEvent(QKeyEvent *event)
{
    //QGraphicsScene::keyPressEvent(event);

    b2Body *body = m_hero->getFixture()->GetBody();

    switch(event->key())
    {
        // arrow up
        case 16777235:
            body->ApplyForce(b2Vec2(5.0f, -20.0f), body->GetWorldCenter());
            break;
        // arrow down
        case 16777237:
            break;
        // arrow left
        case 16777234:
            body->ApplyForce(b2Vec2(-10.0f, 0), body->GetWorldCenter());
            break;
        // arrow right
        case 16777236 :
            body->ApplyForce(b2Vec2(10.0f, 0), body->GetWorldCenter());
            break;
        // button a
        case 65:
            m_hud->toggleRedColor();
            m_hero->toggleRedColor();
            break;
        // button s
        case 83:
            m_hud->toggleGreenColor();
            m_hero->toggleGreenColor();
            break;
        // button d
        case 68 :
            m_hud->toggleBlueColor();
            m_hero->toggleBlueColor();
            break;
        case 16777216 :
            gameView()->changeScene(gameView()->getScene("LevelSelectionScene"));
            break;
        default:
            qDebug() << event->key();
            break;
    }
}

void ActionScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    return;
}

void ActionScene::drawForeground(QPainter *painter, const QRectF &rect)
{
    //painter->drawPixmap(rect.x(), rect.y(), sceneRect().width(), sceneRect().height(), *m_hud);
}

void ActionScene::addBlock(const QRectF &rect, const QPointF &pos, QGraphicsPixmapItem* tile)
{
    b2BodyDef def;
    def.position.Set(P2M(pos.x()), P2M(pos.y()));
    def.userData = tile;
    b2Body *body = m_world->CreateBody(&def);

    b2PolygonShape box;
    box.SetAsBox(P2M(rect.width()/2), P2M(rect.height()/2),
                 b2Vec2(P2M(rect.width()/2), P2M(rect.height()/2)), 0);

    b2Fixture *fixture = body->CreateFixture(&box, 0);

    b2Filter filter;
    fixture->SetFilterData(filter);

    // Setup a circular reference, we can get the body from the item
    // and the item from the body. Dunno if needed though :-)
    tile->setData(0, qVariantFromValue(static_cast<void *>(fixture)));
}

void ActionScene::addBlock(qreal w, qreal h, qreal x, qreal y, QGraphicsPixmapItem* tile)
{
    addBlock(QRectF(0, 0, w, h), QPointF(x, y), tile);
}

void ActionScene::addEdge(const b2Vec2 &v1, const b2Vec2 &v2)
{
    QGraphicsLineItem *li = new QGraphicsLineItem(M2P(v1.x), M2P(v1.y),
                                                  M2P(v2.x), M2P(v2.y));
    li->setPen(QPen(Qt::transparent));
    addItem(li);

    b2BodyDef def;
    b2Body *body = m_world->CreateBody(&def);

    b2EdgeShape edge;
    edge.Set(v1, v2);

    b2FixtureDef fixdef;
    fixdef.friction = 0.25f;
    fixdef.density = 0;
    fixdef.shape = &edge;
    fixdef.userData = li;

    b2Fixture *fixture = body->CreateFixture(&fixdef);

    // Setup a circular reference, we can get the fixture from the item
    // and the item from the fixture. Dunno if needed though :-)
    li->setData(0, qVariantFromValue(static_cast<void *>(fixture)));
}

void ActionScene::loadMap(QString target)
{
    QFileInfo f(target);
    m_levelName = f.fileName();

    QSettings set;
    m_levelScore = set.value(m_levelName).toInt();

    m_map = m_mapReader->readMap(target);

    if (m_map == NULL)
    {
        qDebug() << "error:" << m_mapReader->errorString();
        return;
    }

    m_mapRenderer = new Tiled::OrthogonalRenderer(m_map);

    qDebug() << "size" << m_map->width() << "x" << m_map->height();
    qDebug() << "layers" << m_map->layerCount();

    for(int layer = 0; layer < m_map->layerCount(); layer++)
    {
        QString type = m_map->layerAt(layer)->property("type");

        if (type == "solid")
        {
            Tiled::TileLayer* solidTiles = NULL;
            solidTiles = m_map->layerAt(layer)->asTileLayer();

            for(int w = 0; w < solidTiles->width(); w++)
            {
                for (int h = 0; h < solidTiles->height(); h++)
                {
                    Tiled::Cell cell;
                    cell = solidTiles->cellAt(w, h);

                    if(!cell.isEmpty())
                    {
                        QGraphicsPixmapItem *solidTile = new QGraphicsPixmapItem(0, this);
                        solidTile->setData(ITEM_OBJECTNAME, QString("SolidGround"));
                        solidTile->setPos(w * m_map->tileWidth(),
                                          h * m_map->tileHeight());
                        solidTile->setZValue(1);
                        solidTile->setPixmap(cell.tile->image());
                        addBlock(m_map->tileWidth(), m_map->tileHeight(),
                                 w * m_map->tileWidth(),
                                 h * m_map->tileHeight(),
                                 solidTile);
                        m_mapPixmapItems.append(solidTile);
                    }
                }
            }
        }
        else
        {
            QImage img(m_map->width() * m_map->tileWidth(),
                       m_map->height() * m_map->tileHeight(),
                       QImage::Format_ARGB32);

            QPainter painter(&img);
            m_mapRenderer->drawTileLayer(&painter, m_map->layerAt(layer)->asTileLayer());

            QPixmap mapPixmap = QPixmap::fromImage(img);
            m_mapPixmaps.append(mapPixmap);

            qDebug() << "hasAlpha" << mapPixmap.hasAlpha() << "\n"
                     << "hasAlphaChannel" << mapPixmap.hasAlphaChannel();

            QGraphicsPixmapItem* mapPixmapItem = addPixmap(mapPixmap);
            mapPixmapItem->setPos(0, 0);
            mapPixmapItem->setShapeMode(QGraphicsPixmapItem::MaskShape);

            mapPixmapItem->setPixmap(mapPixmap);

            if (type == "covering")
            {
                mapPixmapItem->setData(ITEM_OBJECTNAME, QString("Covering"));
                mapPixmapItem->setZValue(2);
            }
            else if (type == "coveringBg")
            {
                mapPixmapItem->setData(ITEM_OBJECTNAME, QString("CoveringBg"));
                mapPixmapItem->setZValue(-1);
            }

            m_mapPixmapItems.append(mapPixmapItem);
        }
    }

    QVector<QString> colors;
    colors.append("red"); colors.append("blue"); colors.append("green");

    for (int i = 0; i < colors.size(); i++)
    {
        Tiled::ObjectGroup* color = NULL;

        if(m_map->indexOfLayer(colors.at(i)) >= 0)
            color = m_map->layerAt(m_map->indexOfLayer(colors.at(i)))->asObjectGroup();

        if(color)
        {
            Q_FOREACH(Tiled::MapObject *obj, color->objects())
            {
                Collectible* colorbubble = new Collectible(0, this);
                colorbubble->setData(ITEM_OBJECTNAME, QString(colors.at(i)));
                connect(colorbubble, SIGNAL(removeMe()), this, SLOT(removeSprite()));
                colorbubble->setPos((obj->x()) * m_map->tileWidth(),
                                    (obj->y() - 1) * m_map->tileHeight());

                colorbubble->setZValue(1);

                qDebug() << obj->position() << colorbubble->pos();
            }
        }
    }

    const int w = sceneRect().width() / 8;
    const int h = sceneRect().height();
    // top, bottom, left, right walls
    addEdge(b2Vec2(0, 0), b2Vec2(P2M(w), 0));
    addEdge(b2Vec2(0, P2M(h-1)), b2Vec2(P2M(w), P2M(h-1)));
    addEdge(b2Vec2(0, 0), b2Vec2(0, P2M(h)));
    addEdge(b2Vec2(P2M(w-1), 0), b2Vec2(P2M(w-1), P2M(h)));

    m_hero->bindToWorld(m_world);
    m_hero->updatePosition(100, 100);

    m_clearAlert = false;
}

void ActionScene::unloadMap()
{
    foreach(QGraphicsPixmapItem* removableItem, m_mapPixmapItems)
    {
        removeItem(removableItem);
    }

    for(int i = m_mapPixmapItems.size() - 1; i > 0; i++)
        delete m_mapPixmapItems.at(i);

    m_mapPixmapItems.clear();

    m_mapPixmaps.clear();

    if (m_mapRenderer)
        delete m_mapRenderer;
    if (m_map)
        delete m_map;
}

void ActionScene::removeSprite()
{
    qDebug() << "removing a sprite";

    Sprite* sp = (Sprite*) sender();
    if(sp)
    {
        removeItem(sp);
        sp->deleteLater();
    }
}
