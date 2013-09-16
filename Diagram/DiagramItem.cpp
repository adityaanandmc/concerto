#include "DiagramItem.h"
#include "DiagramTextItem.h"

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>

DiagramItem::DiagramItem(NodeType theType, QMenu *theMenu, QGraphicsItem *theParent)
    : QGraphicsPolygonItem(theParent), theText(new DiagramTextItem(this))
{
    this->theType = theType;
    this->theMenu = theMenu;

    QPainterPath path;
    switch (theType) {
    case ActorType:
        path.moveTo(-15, 70);
        path.arcTo(-15, 50, 20, 20, 180, -90);
        path.lineTo(6.125, 50);
        path.arcTo(6.125, 0, 50, 50, 270, -360);
        path.lineTo(60, 50);
        path.arcTo(60, 50, 20, 20, 90, -90);
        path.lineTo(80, 110);
        path.arcTo(60, 110, 20, 20, 0, -90);
        path.lineTo(60, 130);
        path.lineTo(60, 80);
        path.lineTo(60, 185);
        path.arcTo(32.5, 210, 27.5, 25, 0, -180);
        path.lineTo(32.5, 210);
        path.lineTo(32.5, 130);
        path.lineTo(32.5, 185);
        path.arcTo(5, 210, 27.5, 25, 0, -180);
        path.lineTo(5, 210);
        path.lineTo(5, 80);
        path.lineTo(5, 130);
        path.arcTo(-15, 110, 20, 20, 270, -90);
        path.lineTo(-15, 70);
        thePolygon = path.toFillPolygon();
        setToolTip(QString("Actor"));
        break;

    case UsecaseType:
        path.addEllipse(-100, -50, 200, 100);
        thePolygon = path.toFillPolygon();
        setToolTip(QString("Usecase"));
        break;

    case SubFlowType:
        setPen(QPen(Qt::black, 10));
        path.addEllipse(-25, -25, 50, 50);
        thePolygon = path.toFillPolygon();
        setToolTip(QString("Sub Flow"));
        break;

    case AltFlowType:
        setPen(QPen(Qt::black, 5, Qt::DashLine));
        path.addEllipse(-25, -25, 50, 50);
        thePolygon = path.toFillPolygon();
        setToolTip(QString("Alternate Flow"));
        break;

    case SecFlowType:
        setPen(QPen(Qt::black, 5, Qt::DashDotDotLine));
        path.addEllipse(-25, -25, 50, 50);
        setPen(QPen(Qt::black, 2));
        path.addEllipse(-15, -15, 30, 30);
        thePolygon = path.toFillPolygon();
        setToolTip(QString("Security Flow"));
        break;

    case GeomSquareType:
        setPen(QPen(Qt::black, 6));
        path.addRect(-50, -50, 100, 100);
        setPen(QPen(Qt::black, 2));
        path.addRect(-45, -45, 90, 90);
        thePolygon = path.toFillPolygon();
        setToolTip(QString("Square Note"));
        break;

    case GeomRectangleType:
        path.addRect(-100, -50, 200, 100);
        thePolygon = path.toFillPolygon();
        setToolTip(QString("Rectangle Note"));
        break;

    case GeomCircleType:
        path.addEllipse(-50, -50, 100, 100);
        thePolygon = path.toFillPolygon();
        setToolTip(QString("Circle Note"));
        break;

    case GeomTriangleType:
        thePolygon << QPointF(-60, 50) << QPointF(0, -50) << QPointF(60, 50) << QPointF(-60, 50);
        setToolTip(QString("Tirangle Note"));
        break;

    default:
        thePolygon << QPointF(-120, -80) << QPointF(-70, 80)
                 << QPointF(120, 80) << QPointF(70, -80)
                 << QPointF(-120, -80);
    }

    setPolygon(thePolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void DiagramItem::removeArrow(Arrow *arrow)
{
    int index = theArrows.indexOf(arrow);

    if (index != -1) {
        theArrows.removeAt(index);
    }
}

void DiagramItem::removeArrows()
{
    foreach (Arrow *arrow, theArrows) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void DiagramItem::addArrow(Arrow *arrow)
{
    theArrows.append(arrow);
}

void DiagramItem::setText(const QString& theText)
{
    this->theText->setPlainText(theText);
}

QPixmap DiagramItem::getImage() const
{
    QPixmap pixmap(250, 250);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));
    painter.translate(125, 125);
    painter.drawPolyline(thePolygon);

    return pixmap;
}

void DiagramItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    QList<QAction *> actions = theMenu->actions();

    foreach (QAction *action, actions) {
        action->setEnabled(true);
    }

    theMenu->exec(event->screenPos());
}

QVariant DiagramItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        foreach (Arrow *arrow, theArrows) {
            arrow->updatePosition();
        }
    }

    return value;
}
