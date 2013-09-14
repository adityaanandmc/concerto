#include <QtWidgets>

#include "concerto.h"
#include "ui_concerto.h"

#include "diagramwindow.h"

#include "NodeDefs.h"
#include "RelationDefs.h"

Concerto::Concerto(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Concerto)
{
    ui->setupUi(this);

    this->connectMenuActions();

    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(updateMenus()));

    windowMapper = new QSignalMapper(this);

    connect(
        windowMapper, SIGNAL(mapped(QWidget *)),
        this, SLOT(setActiveSubWindow(QWidget *))
    );
}

Concerto::~Concerto()
{
    delete ui;
}

void Concerto::closeEvent(QCloseEvent *event)
{
    ui->mdiArea->closeAllSubWindows();

    if (ui->mdiArea->currentSubWindow()) {
        event->ignore();
    } else {
        event->accept();
    }
}

void Concerto::connectMenuActions()
{
    // File Menu
    connect(ui->action_New, SIGNAL(triggered()), this, SLOT(newFileAction()));

    // Edit Menu

    // View Menu
    connect(ui->actionS_witch_Layout_Direction, SIGNAL(triggered()), this, SLOT(switchLayoutDirection()));

    // Tools Menu

    // Object Menu

    // Window Menu
    connect(ui->menu_Window, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

    // Help Menu
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(aboutAction()));

    // Pointer Menu
    pointerGroup = new QActionGroup(ui->pointerToolBar);
    pointerGroup->addAction(ui->action_Creator);
    pointerGroup->addAction(ui->action_Relation_Selector);
    pointerGroup->addAction(ui->action_Move);
    pointerGroup->addAction(ui->action_Select);

    ui->action_Creator->setData(DiagramScene::InsertItem);
    ui->action_Relation_Selector->setData(DiagramScene::InsertLine);
    ui->action_Move->setData(DiagramScene::MoveItem);
    ui->action_Select->setData(DiagramScene::SelectItem);

    connect(pointerGroup, SIGNAL(triggered(QAction*)), this, SLOT(updatePointer(QAction*)));
}

void Concerto::connectToolBox(DiagramWindow *subWindow)
{
    QSignalMapper *toolMapper = new QSignalMapper(subWindow);

    // Actors, Usecases, Miscellaneous
    connect(ui->addActorButton, SIGNAL(clicked()), toolMapper, SLOT(map()));
    connect(ui->addUsecaseButton, SIGNAL(clicked()), toolMapper, SLOT(map()));
    connect(ui->addSubFlowButton, SIGNAL(clicked()), toolMapper, SLOT(map()));
    connect(ui->addAltFlowButton, SIGNAL(clicked()), toolMapper, SLOT(map()));
    connect(ui->addSecFlowButton, SIGNAL(clicked()), toolMapper, SLOT(map()));
    connect(ui->addSquareButton, SIGNAL(clicked()), toolMapper, SLOT(map()));
    connect(ui->addRectangleButton, SIGNAL(clicked()), toolMapper, SLOT(map()));
    connect(ui->addCircleButton, SIGNAL(clicked()), toolMapper, SLOT(map()));
    connect(ui->addTriangleButton, SIGNAL(clicked()), toolMapper, SLOT(map()));

    toolMapper->setMapping(ui->addActorButton, static_cast<int>(ActorType));
    toolMapper->setMapping(ui->addUsecaseButton, static_cast<int>(UsecaseType));
    toolMapper->setMapping(ui->addSubFlowButton, static_cast<int>(SubFlowType));
    toolMapper->setMapping(ui->addAltFlowButton, static_cast<int>(AltFlowType));
    toolMapper->setMapping(ui->addSecFlowButton, static_cast<int>(SecFlowType));
    toolMapper->setMapping(ui->addSquareButton, static_cast<int>(GeomSquareType));
    toolMapper->setMapping(ui->addRectangleButton, static_cast<int>(GeomRectangleType));
    toolMapper->setMapping(ui->addCircleButton, static_cast<int>(GeomCircleType));
    toolMapper->setMapping(ui->addTriangleButton, static_cast<int>(GeomTriangleType));

    connect(toolMapper, SIGNAL(mapped(int)), subWindow, SLOT(setItemType(int)));

    // Relations
    QSignalMapper *relationsMapper = new QSignalMapper(subWindow);

    connect(ui->addUnidirectionalAssociationButton, SIGNAL(clicked()), relationsMapper, SLOT(map()));
    connect(ui->addBidirectionalAssociationButton, SIGNAL(clicked()), relationsMapper, SLOT(map()));
    connect(ui->addExtensionPointButton, SIGNAL(clicked()), relationsMapper, SLOT(map()));
    connect(ui->addUsesButton, SIGNAL(clicked()), relationsMapper, SLOT(map()));

    relationsMapper->setMapping(ui->addUnidirectionalAssociationButton, static_cast<int>(UnidirectionalAssociationType));
    relationsMapper->setMapping(ui->addBidirectionalAssociationButton, static_cast<int>(BidirectionalAssociationType));
    relationsMapper->setMapping(ui->addExtensionPointButton, static_cast<int>(ExtensionPointType));
    relationsMapper->setMapping(ui->addUsesButton, static_cast<int>(UsesType));

    connect(relationsMapper, SIGNAL(mapped(int)), subWindow, SLOT(setLineType(int)));

}

void Concerto::connectToolActions(DiagramWindow *subWindow)
{
    QSignalMapper *toolMapper = new QSignalMapper(subWindow);

    // Actors, Usecases, Miscellaneous
    connect(ui->actionAl_ternate_Flow, SIGNAL(triggered()), toolMapper, SLOT(map()));
    connect(ui->actionSub_Flow, SIGNAL(triggered()), toolMapper, SLOT(map()));
    connect(ui->actionSe_curity_Flow, SIGNAL(triggered()), toolMapper, SLOT(map()));
    connect(ui->action_Actor, SIGNAL(triggered()), toolMapper, SLOT(map()));
    connect(ui->action_Use_Case, SIGNAL(triggered()), toolMapper, SLOT(map()));
    connect(ui->action_Circle, SIGNAL(triggered()), toolMapper, SLOT(map()));
    connect(ui->action_Rectangle, SIGNAL(triggered()), toolMapper, SLOT(map()));
    connect(ui->action_Square, SIGNAL(triggered()), toolMapper, SLOT(map()));
    connect(ui->action_Triangle, SIGNAL(triggered()), toolMapper, SLOT(map()));

    toolMapper->setMapping(ui->action_Actor, static_cast<int>(ActorType));
    toolMapper->setMapping(ui->action_Use_Case, static_cast<int>(UsecaseType));
    toolMapper->setMapping(ui->actionSub_Flow, static_cast<int>(SubFlowType));
    toolMapper->setMapping(ui->actionAl_ternate_Flow, static_cast<int>(AltFlowType));
    toolMapper->setMapping(ui->actionSe_curity_Flow, static_cast<int>(SecFlowType));
    toolMapper->setMapping(ui->action_Square, static_cast<int>(GeomSquareType));
    toolMapper->setMapping(ui->action_Rectangle, static_cast<int>(GeomRectangleType));
    toolMapper->setMapping(ui->action_Circle, static_cast<int>(GeomCircleType));
    toolMapper->setMapping(ui->action_Triangle, static_cast<int>(GeomTriangleType));

    connect(toolMapper, SIGNAL(mapped(int)), this, SLOT(toolSelected(int)));

    // Relations
    QSignalMapper *relationsMapper = new QSignalMapper(subWindow);

    connect(ui->action_Unidirectional, SIGNAL(triggered()), relationsMapper, SLOT(map()));
    connect(ui->action_Bidirectional, SIGNAL(triggered()), relationsMapper, SLOT(map()));
    connect(ui->actionUses, SIGNAL(triggered()), relationsMapper, SLOT(map()));
    connect(ui->actionE_xtension_Point, SIGNAL(triggered()), relationsMapper, SLOT(map()));

    relationsMapper->setMapping(ui->action_Unidirectional, static_cast<int>(UnidirectionalAssociationType));
    relationsMapper->setMapping(ui->action_Bidirectional, static_cast<int>(BidirectionalAssociationType));
    relationsMapper->setMapping(ui->actionE_xtension_Point, static_cast<int>(ExtensionPointType));
    relationsMapper->setMapping(ui->actionUses, static_cast<int>(UsesType));

    connect(relationsMapper, SIGNAL(mapped(int)), this, SLOT(lineTypeSelected(int)));
}

void Concerto::connectPointers(DiagramWindow *subWindow)
{
    QSignalMapper *pointerMapper = new QSignalMapper(subWindow);

    connect(ui->action_Creator, SIGNAL(toggled(bool)), pointerMapper, SLOT(map()));
    connect(ui->action_Relation_Selector, SIGNAL(toggled(bool)), pointerMapper, SLOT(map()));
    connect(ui->action_Move, SIGNAL(toggled(bool)), pointerMapper, SLOT(map()));
    connect(ui->action_Select, SIGNAL(toggled(bool)), pointerMapper, SLOT(map()));

    pointerMapper->setMapping(ui->action_Creator, static_cast<int>(DiagramScene::InsertItem));
    pointerMapper->setMapping(ui->action_Relation_Selector, static_cast<int>(DiagramScene::InsertLine));
    pointerMapper->setMapping(ui->action_Move, static_cast<int>(DiagramScene::MoveItem));
    pointerMapper->setMapping(ui->action_Select, static_cast<int>(DiagramScene::SelectItem));

    connect(pointerMapper, SIGNAL(mapped(int)), subWindow, SLOT(setMode(int)));

    connect(subWindow, SIGNAL(nodeInserted()), this, SLOT(nodeInsertFinished()));
}

void Concerto::connectViewActions(DiagramWindow *subWindow)
{
    connect(ui->actionZoom_In, SIGNAL(triggered()), subWindow, SLOT(zoomIn()));
    connect(ui->actionZoom_Out, SIGNAL(triggered()), subWindow, SLOT(zoomOut()));
    connect(ui->action_Normal, SIGNAL(triggered()), subWindow, SLOT(resetZoom()));
    connect(ui->action_Fit_to_Window, SIGNAL(triggered()), subWindow, SLOT(fitWindow()));
}

void Concerto::connectObjectActions(DiagramWindow *subWindow)
{
    connect(ui->action_Remove, SIGNAL(triggered()), subWindow, SLOT(deleteSelectedItem()));
}

void Concerto::newFileAction()
{
    DiagramWindow *theChild = this->createMdiChild();

    connectToolBox(theChild);
    connectPointers(theChild);
    connectViewActions(theChild);
    connectObjectActions(theChild);
    connectToolActions(theChild);

    connect(theChild, SIGNAL(destroyed()), this, SLOT(cleanupSubWindow()));

    theChild->show();
}

void Concerto::aboutAction()
{
    QMessageBox::about(this,
         tr("About useCase Designer"),
         tr("<h1>useCaseDesigner</h1><h5>v0.9.7</h5><br /><br />"
           "The <b>useCase Designer</b> is an interactive<br />"
           "use-case design tool, that visualizes software<br />"
           "complexity and calculates estimated costs.<br /><br />"
           "<center><i>Based on Original Research By</i><br />Prof. Sathis Kumar<br /><br />"
           "<i>Programmed By:</i><br />S. Amrith Nayak</center>"));
}

void Concerto::updateMenus()
{
    bool hasChildWindows = (0 != activeSubWindow());

    ui->actionAl_ternate_Flow->setEnabled(hasChildWindows);
    ui->actionCa_scade->setEnabled(hasChildWindows);
    ui->actionClose_Asll->setEnabled(hasChildWindows);
    ui->actionE_xtension_Point->setEnabled(hasChildWindows);
    ui->actionP_roperties->setEnabled(hasChildWindows);
    ui->actionSave_As->setEnabled(hasChildWindows);
    ui->actionSend_Backward->setEnabled(hasChildWindows);
    ui->actionSend_Forward->setEnabled(hasChildWindows);
    ui->actionSe_curity_Flow->setEnabled(hasChildWindows);
    ui->actionSub_Flow->setEnabled(hasChildWindows);
    ui->actionUses->setEnabled(hasChildWindows);
    ui->action_Actor->setEnabled(hasChildWindows);
    ui->action_Bidirectional->setEnabled(hasChildWindows);
    ui->action_Circle->setEnabled(hasChildWindows);
    ui->action_Close_Window->setEnabled(hasChildWindows);
    ui->action_Next->setEnabled(hasChildWindows);
    ui->action_Previous->setEnabled(hasChildWindows);
    ui->action_Print->setEnabled(hasChildWindows);
    ui->action_Rectangle->setEnabled(hasChildWindows);
    ui->action_Save->setEnabled(hasChildWindows);
    ui->action_Square->setEnabled(hasChildWindows);
    ui->action_Tile->setEnabled(hasChildWindows);
    ui->action_Triangle->setEnabled(hasChildWindows);
    ui->action_Unidirectional->setEnabled(hasChildWindows);
    ui->action_Use_Case->setEnabled(hasChildWindows);
    ui->action_Creator->setEnabled(hasChildWindows);
    ui->action_Select->setEnabled(hasChildWindows);
    ui->action_Move->setEnabled(hasChildWindows);
    ui->action_Relation_Selector->setEnabled(hasChildWindows);
    ui->action_Remove->setEnabled(hasChildWindows);
    ui->action_Properties->setEnabled(hasChildWindows);
    ui->actionZoom_In->setEnabled(hasChildWindows);
    ui->actionZoom_Out->setEnabled(hasChildWindows);
    ui->action_Normal->setEnabled(hasChildWindows);
    ui->action_Fit_to_Window->setEnabled(hasChildWindows);
}

void Concerto::updateWindowMenu()
{
    ui->menu_Window->clear();
    ui->menu_Window->addAction(ui->action_Close_Window);
    ui->menu_Window->addAction(ui->actionClose_Asll);
    ui->menu_Window->addSeparator();
    ui->menu_Window->addAction(ui->action_Tile);
    ui->menu_Window->addAction(ui->actionCa_scade);
    ui->menu_Window->addSeparator();
    ui->menu_Window->addAction(ui->action_Next);
    ui->menu_Window->addAction(ui->action_Previous);

    QAction *separatorAct = ui->menu_Window->addSeparator();
    separatorAct->setSeparator(true);

    ui->menu_Window->addAction(separatorAct);

    QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();

    separatorAct->setVisible(!windows.isEmpty());

    for (int i = 0, term = windows.count(); i < term; ++i) {
        DiagramWindow *child = qobject_cast<DiagramWindow *>(windows.at(i));

        QString text;

        if (i < 9) {
            text = tr("&%1 %2").arg(i + 1)
                               .arg("Yello!");
        } else {
            text = tr("%1 %2").arg(i + 1)
                              .arg("Yello!");
        }

        QAction *action  = ui->menu_Window->addAction(text);
        action->setCheckable(true);
        action->setChecked(child == activeSubWindow());

        connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));
        windowMapper->setMapping(action, windows.at(i));
    }
}

void Concerto::updatePointer(QAction *theAction)
{
    switch (static_cast<DiagramScene::Mode>(theAction->data().toInt())) {
    case DiagramScene::InsertItem:
        setCursor(Qt::PointingHandCursor);
        break;

    case DiagramScene::InsertLine:
        setCursor(Qt::SizeBDiagCursor);
        break;

    case DiagramScene::MoveItem:
        setCursor(Qt::SizeAllCursor);
        break;

    case DiagramScene::SelectItem:
        setCursor(Qt::ArrowCursor);
        break;

    default:
        ;
    }
}

void Concerto::nodeInsertFinished()
{
    pointerGroup->actions().at(2)->setChecked(true);
    setCursor(Qt::SizeAllCursor);
}

void Concerto::toolSelected(int theType)
{
    activeSubWindow()->setItemType(theType);
    pointerGroup->actions().at(0)->setChecked(true);
    setCursor(Qt::PointingHandCursor);
}

void Concerto::lineTypeSelected(int theType)
{
    activeSubWindow()->setLineType(theType);
    pointerGroup->actions().at(1)->setChecked(true);
    setCursor(Qt::SizeBDiagCursor);
}

void Concerto::cleanupSubWindow()
{
    setCursor(Qt::ArrowCursor);
    if (QAction *action = pointerGroup->checkedAction()) {
        action->setChecked(false);
    }
}

DiagramWindow *Concerto::createMdiChild()
{
    DiagramWindow *theChild = new DiagramWindow(ui->menu_Object);

    ui->mdiArea->addSubWindow(theChild);

    return theChild;
}

DiagramWindow *Concerto::activeSubWindow()
{
    if (QMdiSubWindow *subWindow = ui->mdiArea->activeSubWindow()) {
        return qobject_cast<DiagramWindow *>(subWindow->widget());
    }

    return 0;
}

void Concerto::setActiveSubWindow(QWidget *window)
{
    if (!window) {
        return;
    }

    ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

void Concerto::switchLayoutDirection()
{
    if (layoutDirection() == Qt::LeftToRight) {
        qApp->setLayoutDirection(Qt::RightToLeft);
    } else {
        qApp->setLayoutDirection(Qt::LeftToRight);
    }
}
