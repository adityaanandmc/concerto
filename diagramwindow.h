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

    void save(const QString& path);

protected:
    void closeEvent(QCloseEvent *event);
    virtual void wheelEvent(QWheelEvent* event);

    void setupMenu();

signals:
    void nodeInserted();
    void contextMenuDisable();
    void contextMenuEnable();
    void formatMenuDisable();
    void formatMenuEnable();
    void formatFontSettingsChange(const QFont);

public slots:
    void setItemType(int theItemType);
    void setLineType(int theLineType);
    void setMode(int theMode);
    void setFont(const QFont& theFont);
    void zoomIn();
    void zoomOut();
    void fitWindow();
    void resetZoom();
    void deleteSelectedItem();
    void bringForward();
    void sendBackward();
    void imbueFillColour(const QColor& theColour);
    void imbueLineColour(const QColor& theColour);
    
private slots:
    void documentWasModified();

    void nodeAdded(const INode *theNode);
    void relationEstablished(const uint16_t thisNodeId, const uint16_t thatNodeId, const IRelation *theRelation);
    void nodeNameChanged(const uint16_t theNodeId, const QString& theText);
    void labelPositionChanged(const uint16_t theNodeId, const QPointF& thePosition);
    void nodePositionsMayHaveChanged();

    void handleSelectionChanged();
    void handleFormatStateChange(bool theState);

private:
    DiagramScene *theScene;
    std::auto_ptr<DocumentModel> theModel;

    double theZoomLevel;

    static int theGeneration;
};

#endif // DIAGRAMWINDOW_H
