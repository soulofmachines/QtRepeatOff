#include "widget.h"
#include <QtGui>
#include <QxtGlobalShortcut>
#include <QxtCommandOptions>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SystemTray tray;

    bool enabled = true;
    QString hotkey = "Meta+C";

    QxtCommandOptions options;
    options.add("disabled", "just run in tray");
    options.alias("disabled", "d");
    options.add("hotkey", "hotkey sequence", QxtCommandOptions::Required);
    options.alias("hotkey", "k");
    options.add("help", "show help");
    options.alias("help", "h");
    options.parse(QCoreApplication::arguments());
    if(options.count("help") || options.showUnrecognizedWarning()) {
        options.showUsage();
        return -1;
    }
    if(options.count("disabled")) {
        enabled = false;
    }
    if(options.count("hotkey")) {
        hotkey = options.value("hotkey").toString();
    }

    if (enabled) {
        tray.offEnable();
    }

    QxtGlobalShortcut* shortcut = new QxtGlobalShortcut();
    QObject::connect(shortcut, SIGNAL(activated()), &tray, SLOT(offTrigger()));
    shortcut->setShortcut(QKeySequence(hotkey));

    return app.exec();
}
