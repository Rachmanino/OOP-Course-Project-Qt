//Completed by 魏甬翔

#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QIcon>
#include <QBrush>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>
#include <QStatusBar>

namespace Ui {
class helpWidget;
}

class helpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit helpWidget(QWidget *parent = nullptr);
    ~helpWidget();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::helpWidget *ui;
};

#endif // HELPWIDGET_H
