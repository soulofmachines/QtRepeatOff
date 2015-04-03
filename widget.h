#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui>

void Function();

class SystemTray : public QWidget {
    Q_OBJECT
private:
    QAction* trayQuit;
    QMenu* trayMenu;
    QSystemTrayIcon* trayIcon;
public:
    SystemTray(QWidget* parent = 0);
    void offEnable();
    void offDisable();
public slots:
    void offTrigger();
    void offTriggerHelper();
    void offIcon();
    void offQuit();
};

#endif // WIDGET_H
