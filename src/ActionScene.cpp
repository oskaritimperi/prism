#include <QPainter>
#include <QPainterPath>
#include <QColor>
#include <QBrush>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

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

    qsrand(QTime::currentTime().msec());

    m_hero = new Hero(this, QPointF(100, 300));
    connect(m_hero, SIGNAL(removeMe()), this, SLOT(removeSprite()));
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

    QImage img(m_map->width() * m_map->tileWidth(),
               m_map->height() * m_map->tileHeight(),
               QImage::Format_ARGB32);

    QPainter painter(&img);
    m_mapRenderer->drawTileLayer(&painter, m_map->layerAt(0)->asTileLayer());

    m_mapPixmap = QPixmap::fromImage(img);

    qDebug() << "hasAlpha" << m_mapPixmap.hasAlpha() << "\n"
             << "hasAlphaChannel" << m_mapPixmap.hasAlphaChannel();

    m_mapPixmapItem = addPixmap(m_mapPixmap);
    m_mapPixmapItem->setPos(0, 0);
    m_mapPixmapItem->setData(ITEM_OBJECTNAME, QString("SolidGround"));
    m_mapPixmapItem->setShapeMode(QGraphicsPixmapItem::MaskShape);
    m_mapPixmapItem->setZValue(1);

    m_mapPixmapItem->setPixmap(m_mapPixmap);

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
