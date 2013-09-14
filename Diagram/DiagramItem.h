#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPixmapItem>
#include <QList>

#include "../NodeType.h"
#include "Arrow.h"

#include "../IIdentifiable.h"

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
class DiagramTextItem;

class DiagramItem : public QGraphicsPolygonItem, public IIdentifiable
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

    void setText(const QString& theText);

    QPixmap getImage() const;

    void setId(const uint16_t& theId)
    {
        this->theId = theId;
    }

    const uint16_t& getId() const
    {
        return theId;
    }

    const DiagramTextItem *getText() const
    {
        return theText;
    }

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    uint16_t theId;
    NodeType theType;
    QPolygonF thePolygon;
    QMenu *theMenu;
    QList<Arrow *> theArrows;

    DiagramTextItem *theText;
};

#endif // DIAGRAMITEM_H
