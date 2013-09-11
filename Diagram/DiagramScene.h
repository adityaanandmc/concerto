#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsScene>
#include <QMenu>

#include "DiagramItem.h"
#include "DiagramTextItem.h"

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode { InsertItem, InsertLine, InsertText, MoveItem };

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
    void itemInserted(DiagramItem *item);
    void textInserted(QGraphicsTextItem *item);
    void itemSelected(QGraphicsItem *item);
    
public slots:
    void setMode(Mode mode);
    void setItemType(NodeType type);
    void setLineType(RelationType type);
    void editorLostFocus(DiagramTextItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    bool isItemChange(int type);

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
};

#endif // DIAGRAMSCENE_H
