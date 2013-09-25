#ifndef INSERTRELATION_H
#define INSERTRELATION_H

#include <QUndoCommand>
#include <sstream>
#include "../diagramwindow.h"
#include "../IRelation.h"
#include "../INode.h"
#include "../RelationUtil.h"

class InsertRelation : public QUndoCommand
{
public:
    explicit InsertRelation(DiagramWindow *theWindow, const IRelation *theRelation, const INode *thisNode, const INode *thatNode)
        : theWindow(theWindow), theRelation(theRelation), thisNode(thisNode), thatNode(thatNode)
    {
        std::ostringstream oss;
        oss << "Related nodes with " << Util::Relation::toString(theRelation->getType());

        setText(QString::fromStdString(oss.str()));
    }

    virtual void undo()
    {
        theWindow->getModel()->breakUp(theRelation);
        theWindow->getScene()->removeRelation(const_cast<INode *>(thisNode), const_cast<INode *>(thatNode));
    }

    virtual void redo()
    {
        theWindow->getModel()->relate(theRelation, thisNode, thatNode);
        theWindow->getScene()->createRelation(const_cast<IRelation *>(theRelation), const_cast<INode *>(thisNode), const_cast<INode *>(thatNode));
    }

private:
    DiagramWindow *theWindow;
    const IRelation *theRelation;
    const INode *thisNode;
    const INode *thatNode;
};

#endif // INSERTRELATION_H
