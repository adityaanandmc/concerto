#ifndef DIAGRAMTEXTITEM_H
#define DIAGRAMTEXTITEM_H

#include <QGraphicsTextItem>

class DiagramTextItem : public QGraphicsTextItem
{
    Q_OBJECT

public:
    enum { Type = 12 };

    DiagramTextItem(QGraphicsItem *parent = 0);

    int type() const
    {
        return Type;
    }

signals:
    void lostFocus(DiagramTextItem *item);
    void selectedChange(DiagramTextItem *item);
    void gainedFocus(DiagramTextItem *item);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void focusOutEvent(QFocusEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void focusInEvent(QFocusEvent *event);
};

#endif // DIAGRAMTEXTITEM_H
