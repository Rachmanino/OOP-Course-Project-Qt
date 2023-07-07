
#include "mainwidget.h"
#include "fadelabel.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWidget w;
    w.show();
    fadeLabel f(&w);
    f.fadeIn();
    return a.exec();
}
