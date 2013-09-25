#ifndef REMOVENODE_H
#define REMOVENODE_H

#include <QUndoCommand>
#include <sstream>
#include "../diagramwindow.h"
#include "../INode.h"
#include "../NodeUtil.h"

class RemoveNode : public QUndoCommand
{
public:
    explicit RemoveNode(DiagramWindow *theWindow, const INode *theNode)
        : theWindow(theWindow), theNode(theNode)
    {
        theRelationMap = theWindow->getModel()->getRelationMap(theNode);

        std::ostringstream oss;
        oss << "Removed " << Util::Node::toString(theNode->getType());

        setText(QString::fromStdString(oss.str()));
    }

    void undo()
    {
        theWindow->getModel()->addNode(theNode);

        std::map<IRelation *, INode *>::const_iterator it, end = theRelationMap.end();
        for (it = theRelationMap.begin(); it != end; ++it) {
            theWindow->getModel()->relate(it->first, theNode, it->second);
        }

        theWindow->getScene()->insertNode(const_cast<INode *>(theNode), theRelationMap);
    }

    void redo()
    {
        theWindow->getModel()->removeNode(theNode);
        theWindow->getScene()->removeNode(const_cast<INode *>(theNode));
    }

private:
    DiagramWindow *theWindow;
    const INode *theNode;
    std::map<IRelation *, INode *> theRelationMap;
};

#endif // REMOVENODE_H
