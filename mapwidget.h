//Completed by 商邑飞 and 吴童

#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QThread>
#include <QString>
#include <QPixmap>
#include <QKeyEvent>
#include <QPainter>

#include <iostream>
#include <stdio.h>
#include <string>

#include "creature.h"
#include "weapon.h"
#include "characterslices.h"
#include "mainwidget.h"

#define DEFAULT_MONSTER_NUM 15

namespace Ui {
class mapWidget;
}

class mapWidget : public QWidget
{
    Q_OBJECT

public:
    Hero* hero;
    QString mapName;
    explicit mapWidget(QWidget *parent = nullptr, Hero* _hero = nullptr, mainWidget* mw = nullptr);
    void playAnimationDebug();
    void CharacterWalk(const QString &);
    void setMainMenu(mainWidget* mw);
    bool admissible(int newX, int newY);

    void load(const QString mapName);
    void save();
    void produceData(const QString mapName);

    void generateMonsters(int num = DEFAULT_MONSTER_NUM);
    void killMonster();//由battleWdiget调用，清除掉地图上与角色战斗的怪物
    //void backToVillage();//战败之后回到村庄

    static QString mapNames[];

    ~mapWidget();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:

private:

    Ui::mapWidget *ui;
    CharacterSlices charaPic;
    mainWidget* mainMenu;
    bool isWalking;
};

#endif // MAPWIDGET_H
