#ifndef CONCERTO_H
#define CONCERTO_H

#include <QMainWindow>

class DiagramWindow;
class QSignalMapper;

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

    DiagramWindow *createMdiChild();
    void updateMenus();
    void updateWindowMenu();
    void setActiveSubWindow(QWidget *window);
    void switchLayoutDirection();

private:
    Ui::Concerto *ui;

    QSignalMapper *windowMapper;

    void connectMenuActions();
    DiagramWindow *activeSubWindow();
};

#endif // CONCERTO_H
