#ifndef CONCERTO_H
#define CONCERTO_H

#include <QMainWindow>

class DiagramWindow;
class QSignalMapper;
class QActionGroup;
class QFontComboBox;
class QToolButton;
class QUndoGroup;
class QUndoView;

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

    void disableContextMenuObject();
    void enableContextMenuObject();
    void enableFormatMenu();
    void disableFormatMenu();

    void currentFontChanged(QFont theFont);
    void reactToFontChange(const QFont& theFont);
    void boldify(bool makeBold);
    void italicize(bool makeItalic);
    void underline(bool makeUnderline);

    void fillColourChanged();
    void fillColourButtonTriggered();

    void lineColourChanged();
    void lineColourButtonTriggered();

    void saveTriggered();
    void saveAsTriggered();
    void loadTriggered();

    void validateChild();
    void summarizeChild();

    void appendToConsole(const QString str);

    void print();
    void exportTo(const int);

private:
    Ui::Concerto *ui;

    QSignalMapper *windowMapper;
    QActionGroup *pointerGroup;
    QFontComboBox *fontCombo;
    QUndoGroup *undoGroup;
    QUndoView *undoView;

    QToolButton *fillColourToolButton;
    QToolButton *lineColourToolButton;
    QAction *fillAction;
    QAction *lineAction;

    bool fBold;
    bool fItalic;
    bool fUnderline;

    QIcon createColourIndicator(const QString& iconPath, const QColor theColour);
    QIcon createColourIcon(const QColor theColour);
    QMenu *createColourPickerMenu(const char *theSlot, const QColor theDefaultColour);

    void connectMenuActions();
    void connectToolbars();
    void connectToolBox(DiagramWindow *subWindow);
    void connectPointers(DiagramWindow *subWindow);
    void connectViewActions(DiagramWindow *subWindow);
    void connectObjectActions(DiagramWindow *subWindow);
    void connectToolActions(DiagramWindow *subWindow);
    void connectFormatActions(DiagramWindow *subWindow);
    void connectFileActions(DiagramWindow *subWindow);
    void connectModelActions(DiagramWindow *subWindow);
    DiagramWindow *activeSubWindow();
};

#endif // CONCERTO_H
