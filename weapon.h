//To be completed

#ifndef WEAPON_H
#define WEAPON_H

#include<QString>

class Weapon {
protected:
    int maxHp;
    int atk;
    int def;
    int mag;

    QString name;
    QString label;
public:
    Weapon(QString, int, int, int, int,  QString _label = "全村最好的武器！");
    void PrintInfo ();
};

#endif // WEAPON_H
