
#include "weapon.h"
#include <QDebug>

Weapon::Weapon (QString _name,
                int _atk ,
                int _def,
                int _mag,
                int _maxHp,
                QString _label):
    maxHp(_maxHp),
    atk(_atk),
    def(_def),
    mag(_mag),  //释放技能的点数

    name(_name),
    label(_label)
{
    qDebug() << "Weapon" << name << "gained!";
    qDebug() << label;
}

void Weapon::PrintInfo () {
    qDebug() << "Weapon's name:"<<name;
    qDebug() << label;
    qDebug() << "maxHp = "<<maxHp;
    qDebug() << "atk = "<<atk;
    qDebug() << "def = "<<def;
    qDebug() << "mag = "<<mag;
}


