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
    theItemColor = Qt::white;
    theTextColor = Qt::black;
    theLineColor = Qt::black;
}

void DiagramScene::setLineColor(const QColor &color)
{
    theLineColor = color;

    if (isItemChange(Arrow::Type)) {
        Arrow *item = qgraphicsitem_cast<Arrow *>(selectedItems().first());
        item->setColor(theLineColor);

        update();
    }
}

void DiagramScene::setTextColor(const QColor &color)
{
    theTextColor = color;

    if (isItemChange(DiagramTextItem::Type)) {
        DiagramTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
        item->setDefaultTextColor(theTextColor);
    }
}

void DiagramScene::setItemColor(const QColor &color)
{
    theItemColor = color;

    if (isItemChange(DiagramItem::Type)) {
        DiagramItem *item = qgraphicsitem_cast<DiagramItem *>(selectedItems().first());
        item->setBrush(theItemColor);
    }
}

void DiagramScene::setFont(const QFont &font)
{
    theFont = font;

    if (isItemChange(DiagramTextItem::Type)) {
        QGraphicsTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());

        if (item) {
            item->setFont(theFont);
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
        nodeNameChanged(theParent->getId(), item->toHtml());
    }
}

void DiagramScene::addNode(QPointF thePlace)
{
    DiagramItem *item;

    item = new DiagramItem(theItemType, theItemMenu);
    item->setBrush(theItemColor);
    addItem(item);

    item->setPos(thePlace);
    item->setId(DiagramScene::theGeneration);

    INode *theNode = NodeFactory::makeNode(theItemType);
    item->setText(tr("Node %1").arg(DiagramScene::theGeneration));

    connect(item->getText(), SIGNAL(lostFocus(DiagramTextItem*)), this, SLOT(editorLostFocus(DiagramTextItem*)));
    connect(item->getText(), SIGNAL(selectedChange(DiagramTextItem*)), this, SLOT(nodeLabelPositionChanged(DiagramTextItem*)));

    if (ILabelizable *mutator = dynamic_cast<ILabelizable *>(theNode)) {
        mutator->setName(tr("Node %1").arg(DiagramScene::theGeneration).toStdString());
    }

    if (IStylable *mutator = dynamic_cast<IStylable *>(theNode)) {
        mutator->SetFill(theItemColor);
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
        line->setPen(QPen(theLineColor, 2));
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
        textItem->setDefaultTextColor(theTextColor);
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
        emit itemsMayHaveMoved();
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

            bool isClear = true;

            {
                INode *tester = NodeFactory::makeNode(startItem->getType());

                isClear = tester->relatableWith(endItem->getType());

                delete tester;
            }

            if (isClear) {
                Arrow *arrow = new Arrow(startItem, endItem, theLineType);
                arrow->setColor(theLineColor);
                startItem->addArrow(arrow);
                endItem->addArrow(arrow);
                arrow->setZValue(-1000.0);
                addItem(arrow);
                arrow->updatePosition();

                IRelation *theRelation = RelationFactory::makeRelation(theLineType);

                emit relationEstablished(startItem->getId(), endItem->getId(), theRelation);
            }
        }
    }

    line = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void DiagramScene::keyReleaseEvent(QKeyEvent *event)
{
    if (Qt::Key_Delete == event->key()) {
        QList<QGraphicsItem *> items = selectedItems();

        foreach (QGraphicsItem *anItem, items) {
            if (Arrow *anArrow = dynamic_cast<Arrow *>(anItem)) {
                emit relationBroken(anArrow->startItem()->getId(), anArrow->endItem()->getId());
            } else if (DiagramItem *aNode = dynamic_cast<DiagramItem *>(anItem)) {
                emit itemRemoved(aNode->getId());
            }
        }
    }
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
