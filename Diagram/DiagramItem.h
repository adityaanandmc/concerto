#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPixmapItem>
#include <QList>

#include "../NodeType.h"
#include "Arrow.h"


class QPixmap;
class QGraphicsItem;
class QGraphicsScene;
class QTextEdit;
class QGraphicsSceneMouseEvent;
class QMenu;
class QGraphicsSceneContextMenuEvent;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QPolygonF;

class DiagramItem : public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 15 };

    DiagramItem(NodeType theType, QMenu *theMenu, QGraphicsItem *theParent = 0);

    void removeArrow(Arrow *arrow);
    void removeArrows();
    void addArrow(Arrow *arrow);

    NodeType getType() const
    {
        return theType;
    }

    QPolygonF getPolygon() const
    {
        return thePolygon;
    }

    int type() const
    {
        return Type;
    }

    QPixmap getImage() const;

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    NodeType theType;
    QPolygonF thePolygon;
    QMenu *theMenu;
    QList<Arrow *> theArrows;
};

#endif // DIAGRAMITEM_H
