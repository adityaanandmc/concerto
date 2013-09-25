#ifndef INSERTNODE_H
#define INSERTNODE_H

#include <QUndoCommand>
#include <sstream>
#include "../diagramwindow.h"
#include "../INode.h"
#include "../NodeUtil.h"

class InsertNode : public QUndoCommand
{
public:
    explicit InsertNode(DiagramWindow *theWindow, const INode *theNode)
        : theWindow(theWindow), theNode(theNode)
    {
        theRelationMap = theWindow->getModel()->getRelationMap(theNode);

        std::ostringstream oss;
        oss << "Added " << Util::Node::toString(theNode->getType());

        setText(QString::fromStdString(oss.str()));
    }

    virtual void undo()
    {
        theWindow->getModel()->removeNode(theNode);
        theWindow->getScene()->removeNode(const_cast<INode *>(theNode));
    }

    virtual void redo()
    {
        theWindow->getModel()->addNode(theNode);
        theWindow->getScene()->insertNode(const_cast<INode *>(theNode), theRelationMap);
    }

private:
    DiagramWindow *theWindow;
    const INode *theNode;
    std::map<IRelation *, INode *> theRelationMap;
};

#endif // INSERTNODE_H
