#include "position.h"
#include "plannerdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainDisplay *display = new MainDisplay(0);
    display->setWindowTitle("GUI - Semesterprojekt 3");

    display->show();

    return a.exec();
}
