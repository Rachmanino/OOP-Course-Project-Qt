
#include "creature.h"
#include <QDebug>

//#define DEFAULT_PICID 3
#define DEFAULT_MAGNIFICATION 1

Creature::Creature (int _maxHp,
                   int _atk ,
                   int _def,
                   int _mag,
                   QString _name, QLabel * tachi):
    maxHp(_maxHp),
    hp(_maxHp),
    atk(_atk),
    def(_def),
    mag(_mag),  //释放技能的点数
    name(_name),
    tachie(tachi)
{

}
void Creature::labelShake(int radius)
{
    QLabel & lb = *tachie;
    int delayTime = 60;
    QPoint lbPosition = lb.pos();
    lb.move(lbPosition+QPoint(-radius, 0));
    CharacterSlices::delay(delayTime);
    lb.move(lbPosition+QPoint(-radius, -radius));
    CharacterSlices::delay(delayTime);
    //lb.move(lbPosition+QPoint(0, -radius));
    //CharacterSlices::delay(delayTime);
    //lb.move(lbPosition+QPoint(radius, 0));
    //CharacterSlices::delay(delayTime);
    lb.move(lbPosition+QPoint(radius, radius));
    CharacterSlices::delay(delayTime);
    lb.move(lbPosition+QPoint(0, radius));
    CharacterSlices::delay(delayTime);
    lb.move(lbPosition);
}
void Creature::labelShakeMirror(int radius)
{
    QLabel & lb = *tachie;
    int delayTime = 50;
    QPoint lbPosition = lb.pos();
    lb.move(lbPosition+QPoint(radius, -radius));
    CharacterSlices::delay(delayTime);
    lb.move(lbPosition+QPoint(0, -radius));
    CharacterSlices::delay(delayTime);
    //lb.move(lbPosition+QPoint(radius, 0));
    //CharacterSlices::delay(delayTime);
    //lb.move(lbPosition+QPoint(0, radius));
    //CharacterSlices::delay(delayTime);
    lb.move(lbPosition+QPoint(-radius, 0));
    CharacterSlices::delay(delayTime);
    lb.move(lbPosition+QPoint(-radius, radius));
    CharacterSlices::delay(delayTime);
    lb.move(lbPosition);
}
int Creature::DealDamage (double rate, Creature& enemy) {
    int preHp = enemy.hp;
    enemy.hp = std::max(enemy.hp-(std::max(0, int(atk*rate)-enemy.def)), 0); //伤害结算方式，可后续更改
    return preHp-enemy.hp;
}
int Creature::DealRecovery (double rate) {
    int preHp = hp;
    hp = std::min(hp+int(rate*mag), maxHp);
    return hp-preHp;
}

Creature::~Creature()
{
    if (tachie != nullptr)
        delete tachie;
}
void Creature::Revive() {
    hp = maxHp;
}

int Hero::IniMaxHp = 200;
int Hero::IniAtk = 20;
int Hero::IniDef = 0;
int Hero::IniMag = 5;
QString Hero::IniName = "You";

Hero::Hero (int _maxHp,
           int _atk,
           int _def,
           int _mag,
           QString _name,
           Weapon* _pWeapon,
           QLabel* tachi
    ):
    Creature(_maxHp, _atk , _def, _mag, _name, tachi),
    pWeapon(_pWeapon),
    picId(DEFAULT_PICID)
{
    qDebug() << "Hero" << name << "constucted!";
}
Hero::~Hero() {
    qDebug() << "Hero" << name << "destructed!";
}

void Hero::PrintInfo () {
    qDebug() << "Hero's name:" << name;
    qDebug() << "maxHp = " << maxHp;
    qDebug() << "hp = " << hp;
    qDebug() << "atk = " << atk;
    qDebug() << "def = " << def;
    qDebug() << "mag = " << mag;

    if (pWeapon != nullptr) {
        qDebug() << "His weapon is:";
        pWeapon->PrintInfo();
    }
}

void Hero::ChangeWeapon (Weapon* pNewWeapon) {
    pWeapon = pNewWeapon;
}

void Hero::SelectFigure(int _picId) {
    picId = _picId;
}

//Monster function
Monster::Monster():Creature(0, 0, 0, 0, "", nullptr)
{
}
Monster::Monster(int _maxHp,
                 int _atk,
                 int _def,
                 int _mag,
                 QString _name,
                 QLabel* tachi):
    Creature(_maxHp, _atk, _def, _mag, _name, tachi)
{
}
Monster::~Monster(){}

//类的定义和函数原型写在头文件中
//静态成员初始化和函数定义都要写在同名cpp中

//TODO:Hero类添加Skill，Weapon， State成员（先实现这两个类）
