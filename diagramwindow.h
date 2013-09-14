#ifndef DIAGRAMWINDOW_H
#define DIAGRAMWINDOW_H

#include <QGraphicsView>
#include <QMenu>

#include <memory>

#include "Diagram/DiagramScene.h"

class DocumentModel;

class DiagramWindow : public QGraphicsView
{
    Q_OBJECT
public:
    explicit DiagramWindow(QMenu *theObjectMenu);

    QString getTitle() const;

protected:
    void closeEvent(QCloseEvent *event);
    virtual void wheelEvent(QWheelEvent* event);

    void setupMenu();

signals:
    void nodeInserted();

public slots:
    void setItemType(int theItemType);
    void setLineType(int theLineType);
    void setMode(int theMode);
    void zoomIn();
    void zoomOut();
    void fitWindow();
    void resetZoom();
    void deleteSelectedItem();
    
private slots:
    void documentWasModified();

    void nodeAdded(const INode *theNode);
    void relationEstablished(const uint16_t thisNodeId, const uint16_t thatNodeId, const IRelation *theRelation);
    void nodeNameChanged(const uint16_t theNodeId, const QString& theText);
    void labelPositionChanged(const uint16_t theNodeId, const QPointF& thePosition);
    void nodePositionsMayHaveChanged();

private:
    DiagramScene *theScene;
    std::auto_ptr<DocumentModel> theModel;

    double theZoomLevel;

    static int theGeneration;
};

#endif // DIAGRAMWINDOW_H
