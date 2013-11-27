#ifndef DIAGRAMWINDOW_H
#define DIAGRAMWINDOW_H

#include <QGraphicsView>
#include <QMenu>
#include <QUndoStack>

#include <memory>

#include "Diagram/DiagramScene.h"
#include "IDocumentModel.h"

class DocumentModel;

class DiagramWindow : public QGraphicsView
{
    Q_OBJECT
public:
    explicit DiagramWindow(QMenu *theObjectMenu);

    QString getTitle() const;

    const QString& getSavePath() const
    {
        return theSavePath;
    }

    void setSavePath(const QString str)
    {
        theSavePath = str;
    }

    QUndoStack *getUndoStack() const
    {
        return theUndoStack;
    }

    DocumentModel *getModel() const
    {
        return theModel.get();
    }

    DiagramScene *getScene() const
    {
        return theScene;
    }

    bool save();
    bool saveAs(const QString path);
    bool load(const QString path);

    void print();
    void exportTo(const QString path);

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
    void outputToConsole(const QString);
    void documentWasModified();

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
    void propertiesRequested();
    void validate();
    void tabulateModel();
    void modelPropertiesRequested();
    
private slots:
    void nodeAdded(const INode *theNode);
    void nodeRemoved(const uint16_t theId);
    void relationEstablished(const uint16_t thisNodeId, const uint16_t thatNodeId, const IRelation *theRelation, bool record);
    void nodeNameChanged(const uint16_t theNodeId, const QString& theText);
    void labelPositionChanged(const uint16_t theNodeId, const QPointF& thePosition);
    void nodePositionsMayHaveChanged();

    void handleSelectionChanged();
    void handleFormatStateChange(bool theState);

private:
    DiagramScene *theScene;
    std::auto_ptr<DocumentModel> theModel;
    QUndoStack *theUndoStack;
    QString theSavePath;

    void reflectModel();

    void followFlow(vertex_t theVertex, int& subFlowCount, int& altFlowCount, int& secFlowCount, int& extendsCount, int& includesCount);

    double theZoomLevel;

    static int theGeneration;
};

#endif // DIAGRAMWINDOW_H
