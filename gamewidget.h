
#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H


#include <QWidget>
#include <QLabel>
#include <QThread>
#include <QString>
#include <QPixmap>

#include "creature.h"
#include "weapon.h"
#include "characterslices.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class gameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit gameWidget(QWidget *parent = nullptr);
    void playAnimationDebug();
    void CharaterWalk(const QString &);

signals:

private:
    CharacterSlices charaPic;
    Ui::Widget *ui;
    bool isWalking;
};

#endif // GAMEWIDGET_H
