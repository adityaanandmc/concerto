#ifndef CONCERTO_H
#define CONCERTO_H

#include <QMainWindow>

class DiagramWindow;
class QSignalMapper;
class QActionGroup;

namespace Ui {
class Concerto;
}

class Concerto : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Concerto(QWidget *parent = 0);
    ~Concerto();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newFileAction();
    void aboutAction();

    DiagramWindow *createMdiChild();
    void updateMenus();
    void updateWindowMenu();
    void setActiveSubWindow(QWidget *window);
    void switchLayoutDirection();

    void updatePointer(QAction *theAction);
    void cleanupSubWindow();

    void nodeInsertFinished();

    void toolSelected(int theType);
    void lineTypeSelected(int theType);

private:
    Ui::Concerto *ui;

    QSignalMapper *windowMapper;
    QActionGroup *pointerGroup;

    void connectMenuActions();
    void connectToolBox(DiagramWindow *subWindow);
    void connectPointers(DiagramWindow *subWindow);
    void connectViewActions(DiagramWindow *subWindow);
    void connectObjectActions(DiagramWindow *subWindow);
    void connectToolActions(DiagramWindow *subWindow);
    DiagramWindow *activeSubWindow();
};

#endif // CONCERTO_H
