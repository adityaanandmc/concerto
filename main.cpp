#include "concerto.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Concerto w;
    w.show();
    
    return a.exec();
}
