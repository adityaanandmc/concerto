#ifndef DIAGRAMWINDOW_H
#define DIAGRAMWINDOW_H

#include <QGraphicsView>
#include <QMenu>

#include <memory>

#include "Diagram/DiagramScene.h"

class DiagramWindow : public QGraphicsView
{
    Q_OBJECT
public:
    explicit DiagramWindow(QMenu *theObjectMenu);

protected:
    void closeEvent(QCloseEvent *event);

    void setupMenu();

signals:

public slots:
    void setItemType(int theItemType);
    void setLineType(int theLineType);
    
private slots:
    void documentWasModified();

private:
    DiagramScene *theScene;
};

#endif // DIAGRAMWINDOW_H
