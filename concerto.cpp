#include <QtWidgets>

#include "concerto.h"
#include "ui_concerto.h"

#include "diagramwindow.h"

#include "NodeDefs.h"
#include "RelationDefs.h"
#include "DocumentModel.h"

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

    std::auto_ptr<IDocumentModel> model(new DocumentModel("Test", "A sample diagram"));
    std::auto_ptr<INode> thisNode(new ActorNode()), thatNode(new UsecaseNode());
    std::auto_ptr<IRelation> theRelation(new UnidirectionalAssociation());

    model->addNode(thisNode.get());
    model->addNode(thatNode.get());

    model->relate(theRelation.get(), thisNode.get(), thatNode.get());
    qDebug("Model set up successfully!");
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

void Concerto::newFileAction()
{
    DiagramWindow *theChild = this->createMdiChild();

    connectToolBox(theChild);

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
