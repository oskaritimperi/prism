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

#include "ActionScene.h"

using Tiled::Map;
using Tiled::MapReader;
using Tiled::OrthogonalRenderer;
using Tiled::Layer;
using Tiled::ObjectGroup;
using Tiled::Tile;

ActionScene::ActionScene(const QString &name, const QRectF &rect, GameView *parent)
    : GameScene(name, parent)
{
    setSceneRect(rect);
    m_clearAlert = false;
    m_mapReader = new MapReader;

    m_map = 0;
    m_mapRenderer = 0;

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

    m_mapRenderer = new OrthogonalRenderer(m_map);

    qDebug() << "size" << m_map->width() << "x" << m_map->height();
    qDebug() << "layers" << m_map->layerCount();

    for(int layer = 0; layer < m_map->layerCount(); layer++)
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

        QString type = m_map->layerAt(layer)->property("type");

        if (type == "solid")
        {
            mapPixmapItem->setData(ITEM_OBJECTNAME, QString("SolidGround"));
            mapPixmapItem->setZValue(1);
        }
        else if (type == "covering")
        {
            mapPixmapItem->setData(ITEM_OBJECTNAME, QString("Covering"));
            mapPixmapItem->setZValue(2);
        }

        mapPixmapItem->setPixmap(mapPixmap);

        m_mapPixmapItems.append(mapPixmapItem);
    }

    ObjectGroup* fish = NULL;

    if(m_map->indexOfLayer("fish") >= 0)
        fish = m_map->layerAt(m_map->indexOfLayer("fish"))->asObjectGroup();

    if(fish)
    {
        Q_FOREACH(Tiled::MapObject *obj, fish->objects())
        {
            Collectible *fish = new Collectible(0, this);
            fish->setData(ITEM_OBJECTNAME, QString("fish"));
            connect(fish, SIGNAL(removeMe()), this, SLOT(removeSprite()));

            fish->setPos((obj->x()) * m_map->tileWidth(),
                         (obj->y() - 1) * m_map->tileHeight());

            fish->setZValue(2);

            qDebug() << obj->position() << fish->pos();
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
