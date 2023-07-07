//To be completed

#ifndef CREATURE_H
#define CREATURE_H

#include<QString>
#include <QLabel>
#include<weapon.h>
#include<characterslices.h>

class Creature {
public:
    int maxHp;
    int hp;
    int atk;
    int def;
    int mag;
    QString name;
    QLabel* tachie;//立绘的日语罗马音,对战斗中的立绘进行操作

    Creature(int, int, int, int, QString, QLabel* tachi = nullptr);
    //Creature & operator = (const Creature & creat);
    void baseAttack(Creature & opponent);
    void labelShake(int radius = 20);//radius是立绘晃动的半径
    void labelShakeMirror(int radius = 20);//上一个函数进行镜像翻转
    virtual ~Creature();    //虚析构函数
    void Revive();
    //virtual void DefaultAttack(Creature* pEnemy) = 0;

    int DealDamage (double rate, Creature& enemy);   //伤害结算函数
    int DealRecovery (double rate);
};

class Hero : public Creature {
    Weapon* pWeapon;
public:
    static int IniMaxHp;
    static int IniAtk;
    static int IniDef;
    static int IniMag;
    static QString IniName;

    int picId;

    Hero (int _maxHp = Hero::IniMaxHp,
         int _atk = Hero::IniAtk,
         int _def = Hero::IniDef,
         int _mag = Hero::IniMag,
         QString _name = Hero::IniName,
         Weapon* _pWeapon = nullptr, QLabel* tachi = nullptr);
    ~Hero();    //析构函数

    void PrintInfo ();
    void ChangeWeapon (Weapon*);
    void SelectFigure(int);

    //void DefaultAttack(Creature* pMonster);
};

class Monster : public Creature {
public:
    Monster();
    Monster(int, int, int, int, QString, QLabel* tachi = nullptr);
    ~Monster();

    //void DefaultAttack(Creature* pHero);
};

#endif // CREATURE_H
