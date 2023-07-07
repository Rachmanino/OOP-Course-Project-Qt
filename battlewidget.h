//Completed by 吴童 and 商邑飞

#ifndef BATTLEWIDGET_H
#define BATTLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QThread>
#include <QKeyEvent>

#include "mapwidget.h"
#include "mymusicplayer.h"
#include "soundeffectpalyer.h"

namespace Ui {
    class battleWidget;
}

class battleWidget : public QWidget
{
    Q_OBJECT

public:
    int isGameover = 0;

    explicit battleWidget(QWidget *parent=nullptr, Hero* hero=nullptr, Monster* monster=nullptr);
    void setMap(mapWidget* m);
    ~battleWidget();
    void returnToMap();
    void maintenance();

    void demonstrate(int object, int type, int amount);

private slots:
    void on_baseAttackButton_clicked();
    void monsterAttack();
    void on_fleedButton_clicked();
    void on_skill1Button_clicked();
    void on_skill2Button_clicked();
    void on_skill3Button_clicked();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::battleWidget *ui;
    Hero* hero;
    Monster* monster;
    mapWidget* map;
    soundEffectPalyer sep;
};

#endif // BATTLEWIDGET_H
