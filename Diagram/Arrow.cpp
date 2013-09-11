#include "Arrow.h"
#include "DiagramItem.h"

#include <QPen>
#include <QPainter>

#include <math.h>

const qreal Pi = 3.14;

Arrow::Arrow(DiagramItem *theStartItem, DiagramItem *theEndItem, RelationType theType, QGraphicsItem *parent) :
    QGraphicsLineItem(parent)
{
    this->theStartItem = theStartItem;
    this->theEndItem = theEndItem;

    this->theType = theType;

    setFlag(QGraphicsItem::ItemIsSelectable, true);

    theColour = Qt::black;

    switch(theType) {
    case UnidirectionalAssociationType:
    case BidirectionalAssociationType:
        setPen(QPen(theColour, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    break;

    case ExtensionPointType:
        setPen(QPen(theColour, 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    break;

    case UsesType:
    default:
        setPen(QPen(theColour, 2, Qt::DashDotDotLine, Qt::RoundCap, Qt::RoundJoin));
    }
}

QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(theArrowHead);

    return path;
}

DiagramItem *Arrow::startItem() const
{
    return theStartItem;
}

DiagramItem *Arrow::endItem() const
{
    return theEndItem;
}

void Arrow::updatePosition()
{
    QLineF line(mapFromItem(theStartItem, 0, 0), mapFromItem(theEndItem, 0, 0));

    setLine(line);
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (theStartItem->collidesWithItem(theEndItem)) {
        return;
    }

    QPen myPen = pen();
    myPen.setColor(theColour);
    qreal arrowSize = 20;
    painter->setPen(myPen);
    painter->setBrush(theColour);

    QLineF centerLine(theStartItem->pos().x() + theStartItem->boundingRect().center().x(),
                      theStartItem->pos().y() + theStartItem->boundingRect().center().y(),
                      theEndItem->pos().x() + theEndItem->boundingRect().center().x(),
                      theEndItem->pos().y() + theEndItem->boundingRect().center().y());
    QPolygonF endPolygon = theEndItem->polygon();
    QPointF p1 = endPolygon.first() + theEndItem->pos();
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;

    for (int i = 1; i < endPolygon.count(); ++i) {
        p2 = endPolygon.at(i) + theEndItem->pos();
        polyLine = QLineF(p1, p2);

        QLineF::IntersectType intersectType = polyLine.intersect(centerLine, &intersectPoint);

        if (intersectType == QLineF::BoundedIntersection) {
            break;
        }

        p1 = p2;
    }

    setLine(QLineF(intersectPoint.x(), intersectPoint.y(),
                   theStartItem->pos().x() + theStartItem->boundingRect().center().x(),
                   theStartItem->pos().y() + theStartItem->boundingRect().center().y()));

    double angle = acos(line().dx() / line().length());
    if (line().dy() >= 0) {
        angle = (Pi * 2) - angle;
    }

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                    cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                    cos(angle + Pi - Pi / 3) * arrowSize);

    theArrowHead.clear();
    theArrowHead << line().p1() << arrowP1 << arrowP2;

    painter->drawLine(line());
    painter->drawPolygon(theArrowHead);

    if (BidirectionalAssociationType == theType) {
        QPolygonF theOtherArrowHead;
        theOtherArrowHead.clear();
        theOtherArrowHead << line().p2() << arrowP1 << arrowP2;
        painter->drawPolygon(theOtherArrowHead);
    }

    if (isSelected()) {
        painter->setPen(QPen(theColour, 1, Qt::DashLine));
        QLineF mLine = line();
        mLine.translate(0, 4.0);
        painter->drawLine(mLine);
        mLine.translate(0,-8.0);
        painter->drawLine(mLine);
    }
}
