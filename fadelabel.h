//Completed by 商邑飞

#ifndef FADELABEL_H
#define FADELABEL_H

#include <QLabel>

#define FADELABEL_DELAYTIME 4

class fadeLabel:public QLabel
{
public:
    fadeLabel(QWidget * parent);
    void fadeIn();
    void fadeOut();
};

#endif // FADELABEL_H
