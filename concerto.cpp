#include <QtWidgets>

#include "concerto.h"
#include "ui_concerto.h"

#include "diagramwindow.h"

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

    setUnifiedTitleAndToolBarOnMac(true);
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
}

void Concerto::newFileAction()
{
    DiagramWindow *theChild = this->createMdiChild();

    theChild->show();
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
    DiagramWindow *theChild = new DiagramWindow;

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
