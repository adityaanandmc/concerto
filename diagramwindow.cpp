#include <QtWidgets>
#include "diagramwindow.h"

DiagramWindow::DiagramWindow(QMenu *theObjectMenu)
{
    setAttribute(Qt::WA_DeleteOnClose);

    theScene = new DiagramScene(theObjectMenu, this);
    theScene->setSceneRect(QRectF(0, 0, 5000, 5000));

    setScene(theScene);
}

void DiagramWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void DiagramWindow::documentWasModified()
{

}

void DiagramWindow::setItemType(int theItemType)
{
    theScene->setMode(DiagramScene::InsertItem);
    theScene->setItemType(static_cast<NodeType>(theItemType));
}

void DiagramWindow::setLineType(int theLineType)
{
    theScene->setMode(DiagramScene::InsertLine);
    theScene->setLineType(static_cast<RelationType>(theLineType));
}
