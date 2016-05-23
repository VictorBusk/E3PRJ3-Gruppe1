/*!
 * @file        main.cpp
 * @brief       Start application by showing maindisplay-UI
 * @author      Victor Busk (201409557@post.au.dk)
 */

#include "maindisplay.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainDisplay *display = new MainDisplay(0);
    display->setWindowTitle("GUI - Semesterprojekt 3");

    display->show();

    return a.exec();
}
