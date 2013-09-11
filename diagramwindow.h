#ifndef DIAGRAMWINDOW_H
#define DIAGRAMWINDOW_H

#include <QGraphicsView>

class DiagramWindow : public QGraphicsView
{
    Q_OBJECT
public:
    DiagramWindow();

protected:
    void closeEvent(QCloseEvent *event);

signals:
    
private slots:
    void documentWasModified();
};

#endif // DIAGRAMWINDOW_H
