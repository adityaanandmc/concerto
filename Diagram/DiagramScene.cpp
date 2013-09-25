#include "DiagramScene.h"
#include "Arrow.h"

#include <QTextCursor>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

#include "../NodeFactory.h"
#include "../RelationFactory.h"

int DiagramScene::theGeneration = 1;

DiagramScene::DiagramScene(QMenu *theItemMenu, QObject *parent) :
    QGraphicsScene(parent)
{
    this->theItemMenu = theItemMenu;
    theMode = MoveItem;
    theItemType = UsecaseType;
    theLineType = UnidirectionalAssociationType;
    line = 0;
    textItem = 0;
    theItemColour = Qt::white;
    theTextColour = Qt::black;
    theLineColour = Qt::black;
}

void DiagramScene::setLineColour(const QColor &colour)
{
    theLineColour = colour;

    if (isItemChange(Arrow::Type)) {
        Arrow *item = qgraphicsitem_cast<Arrow *>(selectedItems().first());
        item->setColor(theLineColour);

        update();
    } else if (isItemChange(DiagramItem::Type)) {
        DiagramItem *item = qgraphicsitem_cast<DiagramItem *>(selectedItems().first());

        QPen pen = item->pen();
        pen.setBrush(colour);
        item->setPen(pen);
    }
}

void DiagramScene::setTextColour(const QColor &colour)
{
    theTextColour = colour;

    if (isItemChange(DiagramTextItem::Type)) {
        DiagramTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
        item->setDefaultTextColor(theTextColour);
    }
}

void DiagramScene::setItemColour(const QColor &colour)
{
    theItemColour = colour;

    if (isItemChange(DiagramItem::Type)) {
        DiagramItem *item = qgraphicsitem_cast<DiagramItem *>(selectedItems().first());
        item->setBrush(theItemColour);
    }
}

void DiagramScene::setFont(const QFont &font)
{
    theFont = font;

    if (isItemChange(DiagramTextItem::Type)) {
        QGraphicsTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());

        if (item) {
            QTextCursor cursor = item->textCursor();
            QTextCharFormat fmt = cursor.charFormat(); // may be unnecessary assignment

            if (cursor.hasSelection()) {
                fmt.setFont(font);

                cursor.setCharFormat(fmt);
                item->setTextCursor(cursor);
            } else {
                item->setFont(font);
            }
        }
    }
}

void DiagramScene::setMode(Mode mode)
{
    theMode = mode;
}

void DiagramScene::setItemType(NodeType type)
{
    theItemType = type;
}

void DiagramScene::setLineType(RelationType type)
{
    theLineType = type;
}

void DiagramScene::editorLostFocus(DiagramTextItem *item)
{
    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);

    if (item->toPlainText().isEmpty()) {
        removeItem(item);
        item->deleteLater();
    } else {
        DiagramItem *theParent = dynamic_cast<DiagramItem *>(item->parentItem());
        nodeNameChanged(theParent->getId(), item->toHtml().toHtmlEscaped());
    }

    emit formatStateChanged(false);
}

void DiagramScene::editorHasFocus(DiagramTextItem *item)
{
    emit formatStateChanged(true);
}

void DiagramScene::addNode(QPointF thePlace)
{
    INode *theNode = NodeFactory::makeNode(theItemType);

    if (ILabelizable *mutator = dynamic_cast<ILabelizable *>(theNode)) {
        mutator->setName(tr("Node %1").arg(DiagramScene::theGeneration).toStdString());
    }

    if (IStylable *mutator = dynamic_cast<IStylable *>(theNode)) {
        mutator->SetFill(theItemColour);
        mutator->SetBorderFill(theLineColour);
    }

    if (IPositionable *mutator = dynamic_cast<IPositionable *>(theNode)) {
        mutator->setPosition(thePlace.x(), thePlace.y());
    }

    if (IIdentifiable *mutator = dynamic_cast<IIdentifiable *>(theNode)) {
        mutator->setId(DiagramScene::theGeneration);
        ++theGeneration;
    }

    emit itemInserted(theNode);
}

void DiagramScene::removeNode(INode *theNode)
{
    IIdentifiable *id = dynamic_cast<IIdentifiable *>(theNode);

    if (!id) {
        return;
    }

    foreach (QGraphicsItem *item, items()) {
        if (DiagramItem *theItem = dynamic_cast<DiagramItem *>(item)) {
            if (theItem->getId() == id->getId()) {
                removeItem(item);
                break;
            }
        }
    }
}

void DiagramScene::insertNode(INode *theNode, std::map<IRelation *, INode *> theRelationMap)
{
    DiagramItem *item;

    item = new DiagramItem(theNode->getType(), theItemMenu);

    if (IIdentifiable *mutator = dynamic_cast<IIdentifiable *>(theNode)) {
        item->setId(mutator->getId());
        theGeneration = (mutator->getId() > theGeneration) ? mutator->getId() + 1 : theGeneration;
    }

    if (IStylable *mutator = dynamic_cast<IStylable *>(theNode)) {
        QColor qcolour;
        Colour col = mutator->GetFill();

        qcolour.setRgb(col.r, col.g, col.b, col.a);
        item->setBrush(qcolour);

        col = mutator->GetBorderFill();

        qcolour.setRgb(col.r, col.g, col.b, col.a);
        QPen aPen = item->pen();
        aPen.setBrush(qcolour);

        item->setPen(aPen);
    }

    if (ILabelizable *mutator = dynamic_cast<ILabelizable *>(theNode)) {
        item->setText(QString::fromStdString(mutator->getName()));
        item->setLabelPos(mutator->getLabelX(), mutator->getLabelY());
    }

    addItem(item);

    if (IPositionable *mutator = dynamic_cast<IPositionable *>(theNode)) {
        item->setPos(mutator->getX(), mutator->getY());
        item->setZValue(mutator->getZ());
    }

    connect(item->getText(), SIGNAL(lostFocus(DiagramTextItem*)), this, SLOT(editorLostFocus(DiagramTextItem*)));
    connect(item->getText(), SIGNAL(selectedChange(DiagramTextItem*)), this, SLOT(nodeLabelPositionChanged(DiagramTextItem*)));
    connect(item->getText(), SIGNAL(gainedFocus(DiagramTextItem*)), this, SLOT(editorHasFocus(DiagramTextItem*)));

    if (theRelationMap.size() > 0) {
        std::map<IRelation *, INode *>::const_iterator it, end = theRelationMap.end();

        IIdentifiable *thisOne = dynamic_cast<IIdentifiable *>(theNode);

        for (it = theRelationMap.begin(); it != end; ++it) {
            IIdentifiable *theOther = dynamic_cast<IIdentifiable *>(it->second);

            emit relationEstablished(thisOne->getId(), theOther->getId(), it->first, false);
        }
    }
}

void DiagramScene::createRelation(IRelation *theRelation, INode *thisNode, INode *thatNode)
{
    DiagramItem *thisItem, *thatItem;

    thisItem = thatItem = NULL;

    foreach (QGraphicsItem *item, items()) {
        if (DiagramItem *it = dynamic_cast<DiagramItem *>(item)) {
            if (IIdentifiable *thing = dynamic_cast<IIdentifiable *>(thisNode)) {
                if (thing->getId() == it->getId()) {
                    thisItem = it;
                }
            }

            if (IIdentifiable *thing = dynamic_cast<IIdentifiable *>(thatNode)) {
                if (thing->getId() == it->getId()) {
                    thatItem = it;
                }
            }
        }

        if (thisItem && thatItem) {
            break;
        }
    }

    bool isClear = Node::relatableWith(thisNode->getType(), thatNode->getType());

    if (isClear) {
        Arrow *arrow = new Arrow(thisItem, thatItem, theRelation->getType());

        if (IStylable *style = dynamic_cast<IStylable *>(theRelation)) {
            Colour col = style->GetBorderFill();

            arrow->setColor(QColor(col.r, col.g, col.b, col.a));
        }

        thisItem->addArrow(arrow);
        thatItem->addArrow(arrow);
        arrow->setZValue(-1000.0);
        addItem(arrow);
        arrow->updatePosition();
    }
}

void DiagramScene::removeRelation(INode *thisNode, INode *thatNode)
{
    uint16_t thisId = dynamic_cast<IIdentifiable *>(thisNode)->getId(),
             thatId = dynamic_cast<IIdentifiable *>(thatNode)->getId();

    foreach (QGraphicsItem *item, items()) {
        if (Arrow *arrow = dynamic_cast<Arrow *>(item)) {
            if (arrow->startItem()->getId() == thisId && arrow->endItem()->getId() == thatId) {
                arrow->startItem()->removeArrow(arrow);
                arrow->endItem()->removeArrow(arrow);
                removeItem(arrow);
            }
        }
    }
}

void DiagramScene::moveNode(INode *theNode)
{
    QPointF thePosition;
    uint16_t theId;

    if (IPositionable *pos = dynamic_cast<IPositionable *>(theNode)) {
        thePosition.setX(pos->getX());
        thePosition.setY(pos->getY());
    } else {
        return;
    }

    if (IIdentifiable *idfy = dynamic_cast<IIdentifiable *>(theNode)) {
        theId = idfy->getId();
    }

    foreach (QGraphicsItem *item, items()) {
        if (DiagramItem *it = dynamic_cast<DiagramItem *>(item)) {
            if (it->getId() == theId) {
                it->setPos(thePosition);
                break;
            }
        }
    }
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton) {
        return;
    }

    switch (theMode) {
    case InsertItem:
        addNode(mouseEvent->scenePos());
        break;

    case InsertLine:
        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
        line->setPen(QPen(theLineColour, 2));
        addItem(line);
        break;

    case InsertText:
        textItem = new DiagramTextItem();
        textItem->setFont(theFont);
        textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
        textItem->setZValue(1000.0);
        connect(textItem, SIGNAL(lostFocus(DiagramTextItem*)),
                this, SLOT(editorLostFocus(DiagramTextItem*)));
        connect(textItem, SIGNAL(selectedChange(QGraphicsItem*)),
                this, SIGNAL(itemSelected(QGraphicsItem*)));
        addItem(textItem);
        textItem->setDefaultTextColor(theTextColour);
        textItem->setPos(mouseEvent->scenePos());
        break;

    default:
        ;
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (theMode == InsertLine && line != 0) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    } else if (theMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (line != 0 && theMode == InsertLine) {
        QList<QGraphicsItem *> startItems = items(line->line().p1());

        if (startItems.count() && startItems.first() == line) {
            startItems.removeFirst();
        }

        QList<QGraphicsItem *> endItems = items(line->line().p2());

        if (endItems.count() && endItems.first() == line) {
            endItems.removeFirst();
        }

        removeItem(line);
        delete line;

        if (startItems.count() > 0 && endItems.count() > 0 &&
            startItems.first()->type() == DiagramItem::Type &&
            endItems.first()->type() == DiagramItem::Type &&
            startItems.first() != endItems.first()) {

            DiagramItem *startItem = qgraphicsitem_cast<DiagramItem *>(startItems.first());
            DiagramItem *endItem = qgraphicsitem_cast<DiagramItem *>(endItems.first());

            bool isClear = Node::relatableWith(startItem->getType(), endItem->getType());

            if (isClear) {
                IRelation *theRelation = RelationFactory::makeRelation(theLineType);

                emit relationEstablished(startItem->getId(), endItem->getId(), theRelation, true);
            }
        }
    }

    if (theMode == MoveItem) {
        emit itemsMayHaveMoved();
    }

    line = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

bool DiagramScene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems()) {
        if (item->type() == type) {
            return true;
        }
    }
    return false;
}

void DiagramScene::nodeNameChanged(const uint16_t theNodeId, const QString& theName)
{
    emit changeNodeName(theNodeId, theName);
}

void DiagramScene::nodeLabelPositionChanged(DiagramTextItem *item)
{
    DiagramItem *theParent = dynamic_cast<DiagramItem *>(item->parentItem());
    emit changeLabelPosition(theParent->getId(), item->pos());
}
