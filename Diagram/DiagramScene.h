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

    void setLineColour(const QColor &colour);
    void setTextColour(const QColor &colour);
    void setItemColour(const QColor &colour);
    void setFont(const QFont &font);

    void insertNode(INode *theNode, std::map<IRelation *, INode *> theRelationMap);
    void removeNode(INode *theNode);
    void createRelation(IRelation *theRelation, INode *thisNode, INode *thatNode);
    void removeRelation(INode *thisNode, INode *thatNode);
    void moveNode(INode *theNode);

    const QColor& getTextColour() const
    {
        return theTextColour;
    }

    const QColor& getItemColour() const
    {
        return theItemColour;
    }

    const QColor& getLineColour() const
    {
        return theLineColour;
    }

    static void progressGeneration()
    {
        ++theGeneration;
    }
    
signals:
    void itemInserted(const INode *theNode);
    void itemRemoved(const uint16_t theId);
    void relationEstablished(const uint16_t thisNodeId, const uint16_t thatNodeId, const IRelation *theRelation, bool record);
    void itemSelected(QGraphicsItem *item);
    void changeNodeName(const uint16_t theNodeId, const QString& theName);
    void changeLabelPosition(const uint16_t theNodeId, const QPointF& thePosition);
    void itemsMayHaveMoved();
    void formatStateChanged(bool theState);
    
public slots:
    void setMode(Mode mode);
    void setItemType(NodeType type);
    void setLineType(RelationType type);

private slots:
    void editorLostFocus(DiagramTextItem *item);
    void editorHasFocus(DiagramTextItem *item);
    void nodeNameChanged(const uint16_t theNodeId, const QString& theName);
    void nodeLabelPositionChanged(DiagramTextItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

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
    QColor theTextColour;
    QColor theItemColour;
    QColor theLineColour;

    static int theGeneration;
};

#endif // DIAGRAMSCENE_H
