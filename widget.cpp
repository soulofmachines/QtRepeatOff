#include "widget.h"
#include <QtGui>
#include <X11/XKBlib.h>
#include <unistd.h>

Display *dpy;
XKeyboardControl control;
XKeyboardState state;

Widget::Widget(QWidget *parent) : QWidget(parent) {
    QGridLayout* layout = new QGridLayout;
    QPushButton* close = new QPushButton("Close");
    connect(close, SIGNAL(clicked()), this, SLOT(close()));
    layout->addWidget(close, 0, 0, 1, 1);
    setLayout(layout);
    QtConcurrent::run(Function);
}

Widget::~Widget() {
    control.auto_repeat_mode = true;
}

void Function() {
    control.auto_repeat_mode = false;
    dpy = XOpenDisplay(NULL);
    do {
        sleep(5);
        XGetKeyboardControl(dpy, &state);
        if ((state.global_auto_repeat == AutoRepeatModeOn) || (control.auto_repeat_mode == true)) {
            XChangeKeyboardControl(dpy, KBAutoRepeatMode, &control);
            XFlush(dpy);
        }
    } while (control.auto_repeat_mode == false);
    XCloseDisplay(dpy);
}
