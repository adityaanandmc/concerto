#include <QtWidgets>
#include "diagramwindow.h"

DiagramWindow::DiagramWindow()
{
    setAttribute(Qt::WA_DeleteOnClose);
}

void DiagramWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void DiagramWindow::documentWasModified()
{

}
