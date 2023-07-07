//Completed by 吴童

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QIcon>
#include <QBrush>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QKeyEvent>

#include <iostream>
#include <stdio.h>
#include <string>

#include "creature.h"

QT_BEGIN_NAMESPACE
namespace Ui { class wuyu; }
QT_END_NAMESPACE

class mainWidget : public QWidget

{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = nullptr);
    void startGame ();
    ~mainWidget();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_endButton_clicked();

    void on_startButton_clicked();

    void on_helpButton_clicked();

private:
    Ui::wuyu *ui;
};

#endif // MAINWIDGET_H
