#ifdef QT_WIDGETS_LIB
    #include <QtWidgets>
    #include <QtPrintSupport/QPrinter>
    #include <QtPrintSupport/QPrintDialog>
#else
    #include <QtGui>
    #include <QPrinter>
    #include <QPrintDialog>
#endif
#include "diagramwindow.h"
#include "DocumentModel.h"
#include "ModelMapper.h"
#include "ILabelizable.h"
#include "IPositionable.h"
#include "IStylable.h"
#include "NodePropertiesDialog.h"
#include "ModelPropertiesDialog.h"
#include "Undoable/InsertNode.h"
#include "Undoable/InsertRelation.h"
#include "Undoable/RemoveNode.h"
#include "Undoable/RemoveRelation.h"
#include "Undoable/MoveNode.h"

int DiagramWindow::theGeneration = 1;

DiagramWindow::DiagramWindow(QMenu *theObjectMenu)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    // Maybe later :P [auto-pan]
    setDragMode(RubberBandDrag);

    theUndoStack = new QUndoStack(this);

    theScene = new DiagramScene(theObjectMenu, this);
    theScene->setSceneRect(QRectF(0, 0, 5000, 5000));

    setScene(theScene);
    setSceneRect(theScene->sceneRect());

    theModel.reset(new DocumentModel(tr("Untitled %1").arg(DiagramWindow::theGeneration).toStdString(), std::string("A use-case diagram")));

    connect(theScene, SIGNAL(itemInserted(const INode*)), this, SLOT(nodeAdded(const INode*)));
    connect(theScene, SIGNAL(relationEstablished(uint16_t,uint16_t,const IRelation*, bool)), this, SLOT(relationEstablished(uint16_t,uint16_t,const IRelation*,bool)));
    connect(theScene, SIGNAL(changeNodeName(uint16_t,QString)), this, SLOT(nodeNameChanged(uint16_t,QString)));
    connect(theScene, SIGNAL(changeLabelPosition(uint16_t,QPointF)), this, SLOT(labelPositionChanged(uint16_t,QPointF)));
    connect(theScene, SIGNAL(itemsMayHaveMoved()), this, SLOT(nodePositionsMayHaveChanged()));
    connect(theScene, SIGNAL(selectionChanged()), this, SLOT(handleSelectionChanged()));
    connect(theScene, SIGNAL(formatStateChanged(bool)), this, SLOT(handleFormatStateChange(bool)));

    theZoomLevel = 1;

    ++theGeneration;
}

void DiagramWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void DiagramWindow::wheelEvent(QWheelEvent* event)
{
    if (event->modifiers().testFlag(Qt::ControlModifier)) {
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

        double scaleFactor = 1.15;
        if(event->delta() > 0) {
            // Zoom in
            scale(scaleFactor, scaleFactor);
            theZoomLevel *= 1.15;
        } else {
            // Zooming out
            scale(1.0 / scaleFactor, 1.0 / scaleFactor);
            theZoomLevel /= scaleFactor;
        }
    } else {
        QGraphicsView::wheelEvent(event);
    }
}

void DiagramWindow::zoomIn()
{
    double scaleFactor = 1.15;
    scale(scaleFactor, scaleFactor);

    theZoomLevel *= 1.15;
}

void DiagramWindow::zoomOut()
{
    double scaleFactor = 1.15;
    scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    theZoomLevel /= 1.15;
}

void DiagramWindow::fitWindow()
{
    fitInView(theScene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void DiagramWindow::resetZoom()
{
    double compensatingFactor = 1 / theZoomLevel;
    theZoomLevel = 1;

    scale(compensatingFactor, compensatingFactor);
}

void DiagramWindow::deleteSelectedItem()
{
    theUndoStack->beginMacro(tr("Delete Selected Items"));

    foreach (QGraphicsItem *item, theScene->selectedItems()) {
         if (Arrow *arrow = dynamic_cast<Arrow *>(item)) {
            const INode *thisNode = theModel->getNode(arrow->startItem()->getId()),
                        *thatNode = theModel->getNode(arrow->endItem()->getId());

            if (thisNode && thatNode) {
                theUndoStack->push(new RemoveRelation(this, thisNode, thatNode));
            }
        }
    }

    foreach (QGraphicsItem *item, theScene->selectedItems()) {
        if (DiagramItem *it = dynamic_cast<DiagramItem *>(item)) {
            const INode *theNode = theModel->getNode(it->getId());

            theUndoStack->push(new RemoveNode(this, theNode));
        }
    }

    theUndoStack->endMacro();
}

void DiagramWindow::bringForward()
{
    if (theScene->selectedItems().isEmpty())
        return;

    QList<QGraphicsItem *> overlapItems;

    qreal zValue = 0, refZValue = 0;

    foreach (QGraphicsItem *it, theScene->selectedItems()) {
        if (it->zValue() > refZValue) {
            refZValue = it->zValue();
        }

        overlapItems += it->collidingItems();
    }

    foreach (QGraphicsItem *item, overlapItems) {
        if (refZValue >= zValue/* && item->type() == DiagramItem::Type*/)
            zValue = item->zValue() + 0.1;
    }

    foreach (QGraphicsItem *it, theScene->selectedItems()) {
        it->setZValue(zValue);
    }
}

void DiagramWindow::sendBackward()
{
    if (theScene->selectedItems().isEmpty())
        return;

    QList<QGraphicsItem *> overlapItems;

    qreal zValue = 0, refZValue = 0;

    foreach (QGraphicsItem *it, theScene->selectedItems()) {
        if (it->zValue() < refZValue) {
            refZValue = it->zValue();
        }

        overlapItems += it->collidingItems();
    }

    foreach (QGraphicsItem *item, overlapItems) {
        if (refZValue <= zValue/* && item->type() == DiagramItem::Type*/)
            zValue = item->zValue() - 0.1;
    }

    foreach (QGraphicsItem *it, theScene->selectedItems()) {
        it->setZValue(zValue);
    }
}

QString DiagramWindow::getTitle() const
{
    return QString::fromStdString(theModel.get()->getTitle());
}

void DiagramWindow::setItemType(int theItemType)
{
    theScene->setItemType(static_cast<NodeType>(theItemType));
}

void DiagramWindow::setLineType(int theLineType)
{
    theScene->setLineType(static_cast<RelationType>(theLineType));
}

void DiagramWindow::setMode(int theMode)
{
    theScene->setMode(static_cast<DiagramScene::Mode>(theMode));
}

void DiagramWindow::setFont(const QFont& theFont)
{
    theScene->setFont(theFont);
}

void DiagramWindow::imbueFillColour(const QColor &theColour)
{
    theScene->setItemColour(theColour);

    foreach (QGraphicsItem *anItem, theScene->selectedItems()) {
        if (DiagramItem *item = dynamic_cast<DiagramItem *>(anItem)) {
            INode *theNode = theModel->grabNode(item->getId());

            if (IStylable *theStyler = dynamic_cast<IStylable *>(theNode)) {
                theStyler->SetFill(theColour);
            }
        }
    }
}

void DiagramWindow::imbueLineColour(const QColor &theColour)
{
    theScene->setLineColour(theColour);

    foreach (QGraphicsItem *anItem, theScene->selectedItems()) {
        if (DiagramItem *item = dynamic_cast<DiagramItem *>(anItem)) {
            INode *theNode = theModel->grabNode(item->getId());

            if (IStylable *theStyler = dynamic_cast<IStylable *>(theNode)) {
                theStyler->SetBorderFill(theColour);
            }
        } else if (Arrow *arrow = dynamic_cast<Arrow *>(anItem)) {
            const INode *thisNode = theModel->getNode(arrow->startItem()->getId()),
                        *thatNode = theModel->getNode(arrow->endItem()->getId());

            IRelation *theRelation = theModel->grabRelation(thisNode, thatNode);

            if (IStylable *theStyler = dynamic_cast<IStylable *>(theRelation)) {
                theStyler->SetBorderFill(theColour);
            }
        }
    }
}

void DiagramWindow::propertiesRequested()
{
    QList<QGraphicsItem *> items = theScene->selectedItems();

    if (0 == items.count()) {
        return;
    }

    DiagramItem *item = dynamic_cast<DiagramItem *>(items.first());

    if (item) {
        INode *theNode = theModel->grabNode(item->getId());

        if (IAttributable *nodeAttributes = dynamic_cast<IAttributable *>(theNode)) {
            NodePropertiesDialog *theDialog = new NodePropertiesDialog(nodeAttributes, this);

            if (theDialog->exec() == QDialog::Accepted) {
                std::map<std::string, std::string> theAttributes = theDialog->getSavedAttributes();
                std::map<std::string, std::string>::const_iterator it, end = theAttributes.end();

                for (it = theAttributes.begin(); it != end; ++it) {
                    nodeAttributes->setAttribute(it->first, it->second);
                }
            }
        }
    }
}

void DiagramWindow::modelPropertiesRequested()
{
    ModelPropertiesDialog *prop = new ModelPropertiesDialog(theSavePath, QString::fromStdString(theModel->getTitle()), QString::fromStdString(theModel->getAuthor()->getName()), QString::fromStdString(theModel->getDescription()), this);

    if (prop->exec() == QDialog::Accepted) {
        theModel->setTitle(prop->getModelName().toStdString());
        theModel->setDescription(prop->getDescription().toStdString());
        theModel->grabAuthor()->setName(prop->getAuthor().toStdString());
    }
}

void DiagramWindow::nodeAdded(const INode *theNode)
{
    theUndoStack->push(new InsertNode(this, theNode));

    emit nodeInserted();
}

void DiagramWindow::nodeRemoved(const uint16_t theId)
{
    const INode *theNode = theModel->getNode(theId);

    theUndoStack->push(new RemoveNode(this, theNode));
}

void DiagramWindow::relationEstablished(const uint16_t thisNodeId, const uint16_t thatNodeId, const IRelation *theRelation, bool record)
{
    const INode *thisNode = theModel->getNode(thisNodeId),
                *thatNode = theModel->getNode(thatNodeId);

    if (false == record) {
        theModel->relate(theRelation, thisNode, thatNode);
    } else {
        theUndoStack->push(new InsertRelation(this, theRelation, thisNode, thatNode));
    }
}

void DiagramWindow::nodeNameChanged(const uint16_t theNodeId, const QString &theText)
{
    INode *theNode = theModel->grabNode(theNodeId);

    if (ILabelizable *theLabel = dynamic_cast<ILabelizable *>(theNode)) {
        theLabel->setName(theText.toStdString());
    }
}

void DiagramWindow::labelPositionChanged(const uint16_t theNodeId, const QPointF &thePosition)
{
    INode *theNode = theModel->grabNode(theNodeId);

    if (ILabelizable *theLabel = dynamic_cast<ILabelizable *>(theNode)) {
        // Sets relative position of label to origin of the parent item
        // here, that would be the node
        theLabel->setLabelPosition(thePosition.x(), thePosition.y());
    }
}

void DiagramWindow::nodePositionsMayHaveChanged()
{
    QList<QGraphicsItem *> items = theScene->selectedItems();

    if (items.count() > 1) {
        theUndoStack->beginMacro(tr("Moved selected items"));
    }

    foreach (QGraphicsItem *anItem, items) {
        if (DiagramItem *thisItem = dynamic_cast<DiagramItem *>(anItem)) {
            INode *theNode = theModel->grabNode(thisItem->getId());
            theUndoStack->push(new MoveNode(this, theNode, QPointF(thisItem->x(), thisItem->y())));
        }
    }

    if (items.count() > 1) {
        theUndoStack->endMacro();
    }
}

bool DiagramWindow::save()
{
    ModelMapper theMapper;
    bool fFlag = true;

    theMapper.save(theSavePath.toStdString(), theModel.get(), fFlag);

    return fFlag;
}

bool DiagramWindow::saveAs(const QString path)
{
    ModelMapper theMapper;
    bool fFlag = true;

    theMapper.save(path.toStdString(), theModel.get(), fFlag);

    return fFlag;
}

bool DiagramWindow::load(const QString path)
{
    ModelMapper theMapper;
    bool fFlag = true;

    theMapper.load(path.toStdString(), theModel.get(), fFlag);

    theSavePath = path;

    if (fFlag) {
        reflectModel();
    }

    return fFlag;
}

void DiagramWindow::validate()
{
    if (theModel->validate()) {
        emit outputToConsole(tr("<h3>Model is valid.</h3>"));
    } else {
        emit outputToConsole(tr("<h3>Model is invalid.</h3>"));
    }
}

void DiagramWindow::print()
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);

    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle(tr("Print Document %1").arg(theModel->getTitle().c_str()));
    printer.setOutputFileName(tr("%1.pdf").arg(theModel->getTitle().c_str()));
    printer.setColorMode(QPrinter::Color);
    printer.setCopyCount(1);
    printer.setCollateCopies(true);
    printer.setPrinterName(QString::fromUtf8("Default Printer"));
    printer.setPageSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Landscape);
    printer.setPageMargins(5, 5, 5, 5, QPrinter::Millimeter);

    if(dialog->exec() == QDialog::Accepted) {
        QPainter painter;
        painter.begin(&printer);

        theScene->render(&painter, printer.pageRect(), theScene->itemsBoundingRect(), Qt::KeepAspectRatio);
    }
#endif // QT_NO_PRINTER
}

void DiagramWindow::exportTo(const QString path)
{
    theScene->clearSelection();
    theScene->setSceneRect(theScene->itemsBoundingRect());

    QImage image(theScene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    if (path.endsWith(tr(".jpeg"))) {
        image.fill(Qt::white);
    }

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);

    theScene->render(&painter);
    image.save(path);
}

void DiagramWindow::followFlow(vertex_t theVertex, int &subFlowCount, int &altFlowCount, int &secFlowCount, int &extendsCount, int &includesCount)
{
    GraphType theGraph = theModel->getGraph();
    edge_iterator_t ei, ei_end, next;
    vertex_t targetVertex;
    std::vector<vertex_t> targetVertices;

    bool isSubFlow, isAltFlow, isSecFlow;

    isSubFlow = isAltFlow = isSecFlow = false;

    switch (theGraph[theVertex].theNode->getType()) {
    case SubFlowType:
        isSubFlow = true;
        break;

    case SecFlowType:
        isSecFlow = true;
        break;

    case AltFlowType:
        isAltFlow = true;
        break;

    case UsecaseType:
        // Check for relation-type
        boost::tie(ei, ei_end) = boost::edges(theGraph);
        for (next = ei; ei != ei_end; ei = next) {
            ++next;

            if (theVertex == boost::source(*ei, theGraph)) {
                if (ExtensionPointType == theGraph[*ei].theRelation->getType()) {
                    ++extendsCount;
                } else if (UsesType == theGraph[*ei].theRelation->getType()) {
                    ++includesCount;
                }

                targetVertices.push_back(boost::target(*ei, theGraph));
            } else if (theVertex == boost::target(*ei, theGraph)) {
                if (ExtensionPointType == theGraph[*ei].theRelation->getType()) {
                    ++extendsCount;
                } else if (UsesType == theGraph[*ei].theRelation->getType()) {
                    ++includesCount;
                }
            }
        }
        break;

    default:
        return;
    }

    if (isAltFlow || isSecFlow || isSubFlow) {
        boost::tie(ei, ei_end) = boost::edges(theGraph);

        for (next = ei; ei != ei_end; ei = next) {
            ++next;

            if (theVertex == boost::source(*ei, theGraph)) {
                if (ExtensionPointType == theGraph[*ei].theRelation->getType()) {
                    ++extendsCount;
                } else if (UsesType == theGraph[*ei].theRelation->getType()) {
                    ++includesCount;
                }

                targetVertex = boost::target(*ei, theGraph);

                switch (theGraph[targetVertex].theNode->getType()) {
                case UsecaseType:
                    if (isSubFlow) {
                        ++subFlowCount;
                    } else if (isSecFlow) {
                        ++secFlowCount;
                    } else if (isAltFlow) {
                        ++altFlowCount;
                    }
                    targetVertices.push_back(targetVertex);
                    break;

                case SubFlowType:
                case AltFlowType:
                case SecFlowType:
                    followFlow(targetVertex, subFlowCount, altFlowCount, secFlowCount, extendsCount, includesCount);
                    break;

                default:;
                }
            }
        }
    }

    std::vector<vertex_t> targets;

    std::vector<vertex_t>::const_iterator it, it_end = targetVertices.end(), iit, iit_end;
    for (it = targetVertices.begin(); it != it_end; ++it) {
        targets = theModel->getTargetVertices(*it);
        iit_end = targets.end();

        for (iit = targets.begin(); iit != iit_end; ++iit) {
            followFlow(*iit, subFlowCount, altFlowCount, secFlowCount, extendsCount, includesCount);
        }
    }
}

void DiagramWindow::tabulateModel()
{
    GraphType theGraph = theModel->getGraph();

    QString theHtml = tr("<table border=\"1\" cellpadding=\"4\"><thead><tr><th>The usecase</th><th>Sub Flows</th><th>Alt Flows</th><th>Security Flows</th><th>Extends</th><th>Includes</th><th>Total</th></tr></thead><tbody>");

    {
        vertex_iterator_t vi, vi_end, next;
        edge_iterator_t ei, ei_end, enext;
        vertex_t sourceVertex, targetVertex;
        int subFlowsCount, altFlowsCount, secFlowsCount, extendsCount, includesCount;

        boost::tie(vi, vi_end) = boost::vertices(theGraph);
        for (next = vi; vi != vi_end; vi = next) {
            ++next;

            INode *theNode = theGraph[*vi].theNode;
            ILabelizable *theLabel = dynamic_cast<ILabelizable *>(theNode);

            if (UsecaseType == theNode->getType()) {
                theHtml += tr("<tr><td>%1 <small>&lt;&lt; %2 &gt;&gt;</small></td>").arg(theLabel->getName().c_str()).arg(Util::Node::toString(theNode->getType()).c_str());

                subFlowsCount = altFlowsCount = secFlowsCount = extendsCount = includesCount = 0;

                boost::tie(ei, ei_end) = boost::edges(theGraph);
                for (enext = ei; ei != ei_end; ei = enext) {
                    ++enext;

                    sourceVertex = boost::source(*ei, theGraph);

                    if (theGraph[sourceVertex].theNode == theNode) {
                        targetVertex = boost::target(*ei, theGraph);

                        if (ExtensionPointType == theGraph[*ei].theRelation->getType()) {
                            ++extendsCount;
                        } else if (UsesType == theGraph[*ei].theRelation->getType()) {
                            ++includesCount;
                        }

                        switch(theGraph[targetVertex].theNode->getType()) {
                        case SubFlowType:
                            followFlow(targetVertex, subFlowsCount, altFlowsCount, secFlowsCount, extendsCount, includesCount);
                            break;

                        case AltFlowType:
                            followFlow(targetVertex, subFlowsCount, altFlowsCount, secFlowsCount, extendsCount, includesCount);
                            break;

                        case SecFlowType:
                            followFlow(targetVertex, subFlowsCount, altFlowsCount, secFlowsCount, extendsCount, includesCount);
                            break;

                        default:;
                        }
                    }
                }

                theHtml += tr("<td style=\"text-align:center;\">%1</td><td style=\"text-align:center;\">%2</td><td style=\"text-align:center;\">%3</td><td style=\"text-align:center;\">%4</td><td style=\"text-align:center;\">%5</td><td style=\"text-align:center;\">%6</td></tr>").arg(subFlowsCount).arg(altFlowsCount).arg(secFlowsCount).arg(extendsCount).arg(includesCount).arg((subFlowsCount + altFlowsCount + secFlowsCount + extendsCount + includesCount));
            }
        }
    }

    theHtml += tr("</tbody></table>");

    emit outputToConsole(theHtml);
}

void DiagramWindow::handleSelectionChanged()
{
    QList<QGraphicsItem *> items = theScene->selectedItems();

    if (items.count() == 0) {
        emit contextMenuDisable();
    } else {
        emit contextMenuEnable();
    }
}

void DiagramWindow::handleFormatStateChange(bool theState)
{
    if (false == theState) {
        emit formatMenuDisable();
    } else {
        emit formatMenuEnable();

        // Check for the font under text cursor
        if (theScene->selectedItems().count()) {
            if (QGraphicsTextItem *item = dynamic_cast<QGraphicsTextItem *>(theScene->selectedItems().first())) {
                QTextCursor cursor = item->textCursor();

                if (cursor.hasSelection()) {
                    emit formatFontSettingsChange(cursor.charFormat().font());
                }
            }
        }
    }
}

void DiagramWindow::reflectModel()
{
    GraphType theGraph = theModel->getGraph();

    {
        vertex_iterator_t vi, vi_end, next;

        boost::tie(vi, vi_end) = boost::vertices(theGraph);
        for (next = vi; vi != vi_end; vi = next) {
            ++next;

            INode *theNode = theGraph[*vi].theNode;
            theScene->insertNode(theNode, std::map<IRelation *, INode *>());
        }
    }

    {
        edge_iterator_t ei, ei_end, next;
        vertex_t source, target;

        boost::tie(ei, ei_end) = boost::edges(theGraph);
        for (next = ei; ei != ei_end; ei = next) {
            ++next;

            IRelation *theRelation = theGraph[*ei].theRelation;

            source = boost::source(*ei, theGraph);
            target = boost::target(*ei, theGraph);

            INode *thisNode = theGraph[source].theNode,
                  *thatNode = theGraph[target].theNode;

            theScene->createRelation(theRelation, thisNode, thatNode);
        }
    }

    DiagramScene::progressGeneration();
}
