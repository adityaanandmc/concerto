#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsScene>
#include <QMenu>

#include "DiagramItem.h"
#include "DiagramTextItem.h"

#include "INode.h"
#include "IRelation.h"

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode { InsertItem, InsertLine, InsertText, MoveItem, SelectItem };

    explicit DiagramScene(QMenu *theItemMenu, QObject *parent = 0);

    void setLineColor(const QColor &color);
    void setTextColor(const QColor &color);
    void setItemColor(const QColor &color);
    void setFont(const QFont &font);

    const QColor& getTextColour() const
    {
        return theTextColor;
    }

    const QColor& getItemColour() const
    {
        return theItemColor;
    }

    const QColor& getLineColour() const
    {
        return theLineColor;
    }
    
signals:
    void itemInserted(const INode *theNode);
    void relationEstablished(const uint16_t thisNodeId, const uint16_t thatNodeId, const IRelation *theRelation);
    void itemSelected(QGraphicsItem *item);
    void changeNodeName(const uint16_t theNodeId, const QString& theName);
    void changeLabelPosition(const uint16_t theNodeId, const QPointF& thePosition);
    void itemsMayHaveMoved();
    void relationBroken(const uint16_t thisNodeId, const uint16_t thatNodeId);
    void itemRemoved(const uint16_t theNodeId);
    
public slots:
    void setMode(Mode mode);
    void setItemType(NodeType type);
    void setLineType(RelationType type);

private slots:
    void editorLostFocus(DiagramTextItem *item);
    void nodeNameChanged(const uint16_t theNodeId, const QString& theName);
    void nodeLabelPositionChanged(DiagramTextItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void keyReleaseEvent(QKeyEvent *event);

private:
    bool isItemChange(int type);

    void addNode(QPointF thePlace);

    NodeType theItemType;
    RelationType theLineType;
    QMenu *theItemMenu;
    Mode theMode;

    bool leftButtonDown;
    QPointF startPoint;
    QGraphicsLineItem *line;
    QFont theFont;
    DiagramTextItem *textItem;
    QColor theTextColor;
    QColor theItemColor;
    QColor theLineColor;

    static int theGeneration;
};

#endif // DIAGRAMSCENE_H
