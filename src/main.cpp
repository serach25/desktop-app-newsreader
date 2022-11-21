#include "display.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Display window;
    //window.resize(1000,500);
    window.setWindowState(Qt::WindowMaximized);
    window.setWindowTitle("News Reader");
    window.show();
    return a.exec();
}

