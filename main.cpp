#include "mainwindow.h"
#include <QApplication>
#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //SetProcessAffinityMask(GetCurrentProcess(), 1);     //для запуска на 1 ядре
    MainWindow w;
    w.show();

    return a.exec();
}
