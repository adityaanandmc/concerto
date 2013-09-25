#ifndef REMOVERELATION_H
#define REMOVERELATION_H

#include <QUndoCommand>
#include "../diagramwindow.h"
#include "../RelationUtil.h"

class RemoveRelation : public QUndoCommand
{
public:
    explicit RemoveRelation(DiagramWindow *theWindow, const INode *thisNode, const INode *thatNode)
        : theWindow(theWindow), thisNode(thisNode), thatNode(thatNode)
    {
        theRelation = theWindow->getModel()->getRelation(thisNode, thatNode);

        std::ostringstream oss;
        oss << "Removed " << Util::Relation::toString(theRelation->getType());

        setText(QString::fromStdString(oss.str()));
    }

    void undo()
    {
        theWindow->getModel()->relate(theRelation, thisNode, thatNode);
        theWindow->getScene()->createRelation(const_cast<IRelation *>(theRelation), const_cast<INode *>(thisNode), const_cast<INode *>(thatNode));
    }

    void redo()
    {
        theWindow->getModel()->breakUp(theRelation);
        theWindow->getScene()->removeRelation(const_cast<INode *>(thisNode), const_cast<INode *>(thatNode));
    }

private:
    DiagramWindow *theWindow;
    const INode *thisNode;
    const INode *thatNode;
    const IRelation *theRelation;
};

#endif // REMOVERELATION_H
