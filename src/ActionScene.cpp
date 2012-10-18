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

#include "layer.h"
#include "objectgroup.h"
#include "mapobject.h"
#include "tile.h"
#include "tilelayer.h"

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

    // start setting up the world here
    //b2Vec2 gravity(0.0f, -10.0f);
    //m_physicalWorld = new b2World(gravity);
    //m_physicalWorld->SetAllowSleeping(true);

    // initialize rand here
    qsrand(QTime::currentTime().msec());
    // TODO: implement some logic to randomize color bubbles given to player

    //m_hero = new Hero(this, QPointF(100, 300));
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

    if(m_physicalWorld)
        ;//delete m_physicalWorld;
}

void ActionScene::updateLogic()
{
    if(!m_clearAlert)
    {
        advance();
        update();
    }
}

void ActionScene::keyPressEvent(QKeyEvent *event)
{
    QGraphicsScene::keyPressEvent(event);

    switch(event->key())
    {
        // arrow up
        case 16777235:
            break;
        // arrow down
        case 16777237:
            break;
        // arrow left
        case 16777234:
            break;
        // arrow right
        case 16777236 :
            break;
        // button a
        case 65:
            break;
        // button s
        case 83:
            break;
        // button d
        case 68 :
            break;
        default:
            break;
    }
}

void ActionScene::drawBackground(QPainter *painter, const QRectF &rect)
{

}

void ActionScene::drawForeground(QPainter *painter, const QRectF &rect)
{

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
