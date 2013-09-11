#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>

#include "../RelationType.h"

class DiagramItem;

class Arrow : public QGraphicsLineItem
{
public:
    enum { Type = 8 };

    Arrow(DiagramItem *theStartItem, DiagramItem *theEndItem, RelationType theType, QGraphicsItem *parent = 0);

    int type() const
    {
        return Type;
    }

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void setColor(const QColor &color)
    {
        theColour = color;
    }

    DiagramItem *startItem() const;

    DiagramItem *endItem() const;

    void updatePosition();
    
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    DiagramItem *theStartItem;
    DiagramItem *theEndItem;

    RelationType theType;

    QColor theColour;
    QPolygonF theArrowHead;
};

#endif // ARROW_H
