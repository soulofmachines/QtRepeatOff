#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SystemTray tray;

    if ((argc < 2) || (strcmp(argv[1], "-d") != 0)) {
        tray.offEnable();
    }

    return app.exec();
}
