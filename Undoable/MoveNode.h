#ifndef MOVENODE_H
#define MOVENODE_H

#include <QUndoCommand>
#include <sstream>
#include "../diagramwindow.h"
#include "../NodeUtil.h"
#include "../IPositionable.h"

class MoveNode : public QUndoCommand
{
public:
    explicit MoveNode(DiagramWindow *theWindow, INode *theNode, const QPointF& newPosition)
        : theWindow(theWindow), theNode(theNode), theNewPosition(newPosition)
    {
        if (IPositionable *pos = dynamic_cast<IPositionable *>(theNode)) {
            theOldPosition = QPointF(pos->getX(), pos->getY());
        }

        std::ostringstream oss;
        oss << "Moved " << Util::Node::toString(theNode->getType());

        setText(QString::fromStdString(oss.str()));
    }

    void undo()
    {
        if (IPositionable *thePosition = dynamic_cast<IPositionable *>(theNode)) {
            thePosition->setPosition(theOldPosition.x(), theOldPosition.y());
            theWindow->getScene()->moveNode(theNode);
        }
    }

    void redo()
    {
        if (IPositionable *thePosition = dynamic_cast<IPositionable *>(theNode)) {
            thePosition->setPosition(theNewPosition.x(), theNewPosition.y());
            theWindow->getScene()->moveNode(theNode);
        }
    }

private:
    DiagramWindow *theWindow;
    INode *theNode;
    QPointF theOldPosition;
    QPointF theNewPosition;
};

#endif // MOVENODE_H
