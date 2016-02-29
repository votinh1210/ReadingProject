#include "mainwindow.h"
#include <QApplication>
#include "goldendictLib/hotkeywrapper.hh"

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    QHotkeyApplication a( "LR", argc, argv );
    MainWindow w;

    //a.addDataCommiter( w );
    w.show();
    a.setWindowIcon(QIcon("icon.png"));
    return a.exec();
}
