#include "widget.h"
#include <QtGui>
#include <X11/XKBlib.h>
#include <unistd.h>

QAction* functionTrigger;

Display *dpy;
XKeyboardControl control;
XKeyboardState state;

void Function() {
    control.auto_repeat_mode = false;
    dpy = XOpenDisplay(NULL);
    do {
        sleep(3);
        XGetKeyboardControl(dpy, &state);
        if ((state.global_auto_repeat == AutoRepeatModeOn) || (control.auto_repeat_mode == true)) {
            XChangeKeyboardControl(dpy, KBAutoRepeatMode, &control);
            XFlush(dpy);
        }
        functionTrigger->setChecked(true);
        functionTrigger->setEnabled(true);
    } while (control.auto_repeat_mode == false);
    XCloseDisplay(dpy);
    functionTrigger->setChecked(false);
}

SystemTray::SystemTray(QWidget* parent) : QWidget(parent) {
    functionTrigger = new QAction("&Enable", this);
    trayQuit = new QAction("&Quit", this);
    functionTrigger->setCheckable(true);
    connect(functionTrigger, SIGNAL(triggered()), this, SLOT(offTriggerHelper()));
    connect(functionTrigger, SIGNAL(changed()), this, SLOT(offIcon()));
    connect(trayQuit, SIGNAL(triggered()), this, SLOT(offQuit()));
    trayMenu = new QMenu();
    trayMenu->addAction(functionTrigger);
    trayMenu->addAction(trayQuit);
    trayIcon = new QSystemTrayIcon();
    trayIcon->setContextMenu(trayMenu);
    offIcon();
    trayIcon->show();
}

void SystemTray::offEnable() {
    functionTrigger->setEnabled(false);
    QtConcurrent::run(Function);
}

void SystemTray::offDisable() {
    functionTrigger->setEnabled(false);
    control.auto_repeat_mode = true;
}

void SystemTray::offTrigger() {
    if (functionTrigger->isEnabled()) {
        if (functionTrigger->isChecked()) {
            offDisable();
        } else {
            offEnable();
        }
    }
}

void SystemTray::offTriggerHelper() {
    functionTrigger->setChecked(!functionTrigger->isChecked());
    offTrigger();
}

void SystemTray::offIcon() {
    if (functionTrigger->isChecked()) {
        trayIcon->setIcon(QPixmap(":/enabled.png"));
    } else {
        trayIcon->setIcon(QPixmap(":/disabled.png"));
    }
}

void SystemTray::offQuit() {
    offDisable();
    sleep(5);
    this->close();
}
