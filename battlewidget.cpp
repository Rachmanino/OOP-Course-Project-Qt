#include "battlewidget.h"
#include "ui_battlewidget.h"
#include "characterslices.h"
#include "creature.h"
#include "atkanimation.h"
#include "fadelabel.h"

#include <fstream>
#include <time.h>
#include <stdlib.h>

#define DEFAULT_HERO_ID 2_1
#define LOWER_PLANE 440
#define HP_LOSS_TOTAL_TIME 300
#define FLEED_TOTAL_TIME 200
#define MOVE_TOTAL_TIME 200
#define MOVE_FRAME 110
#define MOVE_DIS 330

#define DEMONSTRATION_HERO 0
#define DEMONSTRATION_MONSTER 1

#define DEMONSTRATION_DAMAGE -1
#define DEMONSTRATION_HEAL 1

int isWorking = 0;

//QSoundEffect effect;

battleWidget::battleWidget(QWidget *parent, Hero* _hero, Monster* _monster) :
    QWidget(parent),
    ui(new Ui::battleWidget), hero(_hero)
{
    ui->setupUi(this);
    monster = new Monster(*_monster);
    hero->tachie = ui->heroLabel;
    monster->tachie = ui->monsterLabel;

    this->setFixedSize(960, 640);
    this->setWindowTitle(QString("战斗！"));
    QPalette palette;

    QImage image("../wuyu/images/battle/battlefield2.png"); // 指定图片所在位置及图片名
    palette.setBrush(this->backgroundRole(), QBrush(image));
    this->setPalette(palette);

    QString heroPath = "../wuyu/images/character/Actor2_1.png";
    QPixmap heroPic(heroPath);
    ui->heroLabel->resize(heroPic.size());
    ui->heroLabel->move(80, LOWER_PLANE-heroPic.height());
    ui->heroLabel->setPixmap(heroPic);

    QString monsterPath = "../wuyu/images/enemies/"+monster->name+".png";
    QPixmap monsterPic(monsterPath);
    ui->monsterLabel->resize(monsterPic.size());
    ui->monsterLabel->move(620, LOWER_PLANE-monsterPic.height());
    ui->monsterLabel->setPixmap(monsterPic);

    ui->resultLabel->hide();
    ui->demonstrationLabel->hide();

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);

    ui->heroHpBar->setPalette(pe);
    ui->monsterHpBar->setPalette(pe);
    ui->heroHpBar->setAlignment(Qt::AlignHCenter);
    ui->monsterHpBar->setAlignment(Qt::AlignHCenter);
    ui->heroHpBar->setMaximum(hero->maxHp);
    ui->monsterHpBar->setMaximum(monster->maxHp);
    ui->heroHpBar->setValue(hero->hp);
    ui->monsterHpBar->setValue(monster->hp);

    ui->logLabel->setText("");//置空战斗log
    ui->logLabel->setStyleSheet("color:white;");

    QString baseAttackStyle("QPushButton{background-color:rgba(70,222,212,100%);\
                                            color: white;   border-radius: 5px;  border: 2px groove gray; border-style: outset;border-color:blue;border-width:5px;}" // 按键本色
        "QPushButton:hover{background-color:white; color: black;}"  // 鼠标停放时的色彩
                                  "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");   // 鼠标按下的色彩
    ui->baseAttackButton->setStyleSheet(baseAttackStyle);

    QString fireStyle("QPushButton{background-color:orange;\
                                            color: white;   border-radius: 5px;  border: 2px groove gray; border-style: outset;border-color:blue;border-width:5px;}" // 按键本色
        "QPushButton:hover{background-color:white; color: black;}"  // 鼠标停放时的色彩
                                  "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");   // 鼠标按下的色彩
    ui->skill1Button->setStyleSheet(fireStyle);

    QString healStyle("QPushButton{background-color:green;\
                                            color: white;   border-radius: 5px;  border: 2px groove gray; border-style: outset;border-color:blue;border-width:5px;}" // 按键本色
        "QPushButton:hover{background-color:white; color: black;}"  // 鼠标停放时的色彩
                                  "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");   // 鼠标按下的色彩
    ui->skill2Button->setStyleSheet(healStyle);

    QString passStyle("QPushButton{background-color:rgb(181,181,181);\
                                            color: white;   border-radius: 5px;  border: 2px groove gray; border-style: outset;border-color:blue;border-width:5px;}" // 按键本色
        "QPushButton:hover{background-color:white; color: black;}"  // 鼠标停放时的色彩
                                  "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");   // 鼠标按下的色彩
    ui->skill3Button->setStyleSheet(passStyle);

    QString otherStyle("QPushButton{background-color:yellow;\
                                            color: black;   border-radius: 30px;  border: 25px groove gray; border-style: outset;border-color:blue;border-width:5px;}" // 按键本色
        "QPushButton:hover{background-color:white; color: black;}"  // 鼠标停放时的色彩
                                  "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");   // 鼠标按下的色彩
    ui->itemButton->setStyleSheet(otherStyle);
    ui->fleedButton->setStyleSheet(otherStyle);

    ui->vsLabel->setStyleSheet("QLabel{color:rgb(241,65,11)};");

    srand(time(0));
    switch (rand()%2) {
        case 0:
            myMusicPlayer::playMusic("battle1", 30);
            break;
        case 1:
            myMusicPlayer::playMusic("battle2", 30);
            break;
    }
}

battleWidget::~battleWidget()
{
    delete ui;
    //delete hero;
}

void hpLossAnimation(QProgressBar& bar, int damage) {
    //qDebug() << damage;
    for (int i = 0; i < damage; ++i){
        bar.setValue(bar.value()-1);
        CharacterSlices::delay(HP_LOSS_TOTAL_TIME/damage);
    }
}
void hpGainAnimation(QProgressBar& bar, int heal) {
    //qDebug() << heal;
    for (int i=0;i<heal;i++) {
        bar.setValue(bar.value()+1);
         CharacterSlices::delay(HP_LOSS_TOTAL_TIME/heal);
    }
}

void battleWidget::setMap(mapWidget* m)
{
    map = m;
}
void battleWidget::monsterAttack()
{
    if (isGameover) return;
    if (isWorking) {
        return;
    } else {
        isWorking = 1;
    }
    for (int i=0;i<MOVE_FRAME;i++) {
        ui->monsterLabel->move(ui->monsterLabel->x()-1.0*MOVE_DIS/MOVE_FRAME, ui->monsterLabel->y());
        CharacterSlices::delay(MOVE_TOTAL_TIME/MOVE_FRAME);
    }
    QString effectName, soundName;
    int startFrame=0, endFrame=0;
    if (monster->name == "Slime")
    {
        effectName = "Water3";
        soundName = "bubble";
        startFrame = 0;
        endFrame = 14;
    }
    else if (monster->name == "Bat")
    {
        effectName = "Darkness1";
        soundName = "sword";
        startFrame = 8;
        endFrame = 15;
    }
    sep.playMusic(soundName, 30);//播放技能特效音效
    atkAnimation effect("../wuyu/images/animations/" + effectName + ".png", this);
    effect.atkEffection(ui->heroLabel->x()+ui->heroLabel->width()/2-WEAPON_APPLY_SIZE/2,
                        ui->heroLabel->y()+ui->heroLabel->height()/2-WEAPON_APPLY_SIZE/2,
                        startFrame, endFrame, 50);
    hero->labelShake();
    int damage =  monster->DealDamage(1.0, *hero);
    demonstrate(DEMONSTRATION_HERO, DEMONSTRATION_DAMAGE, damage);
    for (int i=0;i<MOVE_FRAME;i++) {
        ui->monsterLabel->move(ui->monsterLabel->x()+1.0*MOVE_DIS/MOVE_FRAME, ui->monsterLabel->y());
        CharacterSlices::delay(MOVE_TOTAL_TIME/MOVE_FRAME);
    }

    hpLossAnimation(*ui->heroHpBar, damage);
    ui->demonstrationLabel->hide();

    ui->logLabel->setText(monster->name + "使用了 普通攻击！");
    ui->logLabel->show();
    isWorking = 0;
    CharacterSlices::delay(800);   //log显示0.8秒
    ui->logLabel->hide();

    maintenance();
}
void battleWidget::maintenance() {      //维护血条和胜负判定，未完成
    //qDebug() <<"Function maintenance not completed!";
    if (isGameover) return;
    isWorking = 1;
    //hero->PrintInfo();
    qDebug() << hero->hp << monster->hp;
    if (hero->hp == 0) {
        isGameover = 1;
        ui->resultLabel->resize(this->size());
        ui->resultLabel->move(0,0);
        ui->resultLabel->setPixmap(QPixmap("../wuyu/images/battle/defeat.png"));
        ui->resultLabel->raise();
        ui->resultLabel->show();
        myMusicPlayer::playMusic("defeat");
        CharacterSlices::delay(3000);

        std::fstream is("../wuyu/data/mapWidget/dungeon0.txt", std::ios::in);
        std::fstream os("../wuyu/data/mapWidget/dungeon.txt", std::ios::out | std::ios::trunc);
        while (!is.eof()) {
            char str[1024];
            is.getline(str,sizeof(str),'\n'); //读一行
            os << str <<std::endl; //输出到文件
        }
        is.close();
        os.close();

        isWorking = 0;
        hero->Revive();
        map->load("village");
        returnToMap();
    }
    if (monster->hp == 0) {
        isGameover = 1;
        ui->resultLabel->resize(this->size());
        ui->resultLabel->move(0,0);
        ui->resultLabel->setPixmap(QPixmap("../wuyu/images/battle/victory.png"));
        ui->resultLabel->raise();
        ui->resultLabel->show();
        myMusicPlayer::playMusic("victory");
        CharacterSlices::delay(3000);

        isWorking = 0;
        map->killMonster();
        returnToMap();
    }
    isWorking = 0;
}
void battleWidget::on_baseAttackButton_clicked()
{
    if (isGameover) return;
    if (isWorking) {
        return;
    } else {
        isWorking = 1;
    }

    for (int i=0;i<MOVE_FRAME;i++) {
        ui->heroLabel->move(ui->heroLabel->x()+1.0*MOVE_DIS/MOVE_FRAME, ui->heroLabel->y());
        CharacterSlices::delay(MOVE_TOTAL_TIME/MOVE_FRAME);
    }
    sep.playMusic("sword");//播放技能特效音效
    atkAnimation effect("../wuyu/images/animations/Slash.png", this);
    effect.atkEffection(ui->monsterLabel->x()+ui->monsterLabel->width()/2-WEAPON_APPLY_SIZE/2,
                        ui->monsterLabel->y()+ui->monsterLabel->height()/2-WEAPON_APPLY_SIZE/2,
                        0, 4, 50);
    monster->labelShakeMirror();
    int damage = hero->DealDamage(1.0, *monster);
    demonstrate(DEMONSTRATION_MONSTER, DEMONSTRATION_DAMAGE, damage);
    for (int i=0;i<MOVE_FRAME;i++) {
        ui->heroLabel->move(ui->heroLabel->x()-1.0*MOVE_DIS/MOVE_FRAME, ui->heroLabel->y());
        CharacterSlices::delay(MOVE_TOTAL_TIME/MOVE_FRAME);
    }
    hpLossAnimation(*ui->monsterHpBar, damage);
    ui->demonstrationLabel->hide();

    ui->logLabel->setText(hero->name + "使用了 普通攻击！");
    ui->logLabel->show();
    CharacterSlices::delay(800);
    ui->logLabel->hide();

    maintenance();
    isWorking = 0;

    monsterAttack();
}

void battleWidget::on_fleedButton_clicked()
{
    if (isWorking) return;

    CharacterSlices::delay(FLEED_TOTAL_TIME/2);
    for (int i=0;i<MOVE_FRAME;i++) {
        ui->heroLabel->move(ui->heroLabel->x()-1.0*(ui->heroLabel->x()+1.5*ui->heroLabel->width())/MOVE_FRAME, ui->heroLabel->y()); //这里整除有问题
        CharacterSlices::delay(FLEED_TOTAL_TIME/MOVE_FRAME);
    }
    CharacterSlices::delay(FLEED_TOTAL_TIME/2);

    returnToMap();
}
void battleWidget::returnToMap() {
    fadeLabel f(this);
    f.fadeOut();
    this->close();
    map->show();
    fadeLabel g(map);
    g.fadeIn();
    myMusicPlayer::playMusic(map->mapName);
}

void battleWidget::on_skill1Button_clicked()
{
    if (isGameover) return;
    if (isWorking) {
        return;
    } else {
        isWorking = 1;
    }
    sep.playMusic("explosion", 30);//播放技能特效音效
    atkAnimation effect("../wuyu/images/animations/Explosion1.png", this, 220);
    effect.atkEffection(ui->monsterLabel->x()+ui->monsterLabel->width()/2-WEAPON_APPLY_SIZE/2,
                        ui->monsterLabel->y()+ui->monsterLabel->height()/2-WEAPON_APPLY_SIZE/2,
                        0, 11, 80);
    monster->labelShakeMirror(30);
    int damage = hero->DealDamage(2.0, *monster);
    demonstrate(DEMONSTRATION_MONSTER, DEMONSTRATION_DAMAGE, damage);
    hpLossAnimation(*ui->monsterHpBar, damage);
    ui->demonstrationLabel->hide();

    ui->logLabel->setText(hero->name + "使用了 炎爆术！");
    ui->logLabel->show();
    CharacterSlices::delay(800);
    ui->logLabel->hide();

    maintenance();
    isWorking = 0;

    monsterAttack();
}


void battleWidget::on_skill2Button_clicked()
{
    if (isGameover) return;
    if (isWorking) {
        return;
    } else {
        isWorking = 1;
    }
    sep.playMusic("heal", 100);//播放技能特效音效
    atkAnimation effect("../wuyu/images/animations/Recovery1.png", this, 330);  //最后一个参数代表animation大小
    effect.atkEffection(ui->heroLabel->x()+ui->heroLabel->width()/2-WEAPON_APPLY_SIZE/2,
                        ui->heroLabel->y()+ui->heroLabel->height()/2-WEAPON_APPLY_SIZE/2,
                        0, 14, 50);
    int heal = hero->DealRecovery(8.0);
    demonstrate(DEMONSTRATION_HERO, DEMONSTRATION_HEAL, heal);
    hpGainAnimation(*ui->heroHpBar, heal);
    ui->demonstrationLabel->hide();

    ui->logLabel->setText(hero->name + "使用了 次级治疗术！");
    ui->logLabel->show();
    CharacterSlices::delay(800);
    ui->logLabel->hide();

    maintenance();
    isWorking = 0;

    monsterAttack();
}


void battleWidget::on_skill3Button_clicked()
{
    if (isGameover) return;
    if (isWorking) {
        return;
    } else {
        isWorking = 1;
    }

    ui->logLabel->setText(hero->name + "跳过回合！");
    ui->logLabel->show();
    CharacterSlices::delay(800);
    ui->logLabel->hide();

    maintenance();
    isWorking = 0;

    monsterAttack();
}
void battleWidget::demonstrate (int object, int type, int amount) {
    QLabel* objectLabel = new QLabel;
    if (object == DEMONSTRATION_HERO) objectLabel = ui->heroLabel;
    else if (object == DEMONSTRATION_MONSTER) objectLabel = ui->monsterLabel;

    ui->demonstrationLabel->move(objectLabel->x()+objectLabel->width()/2-ui->demonstrationLabel->width()/2, objectLabel->y()-70);
    QString demonstration;
    if (type == DEMONSTRATION_DAMAGE) {
        ui->demonstrationLabel->setStyleSheet("QLabel{font-size: 40px;"
                                              "color: red}");
        demonstration += "-";
    }
    else if (type == DEMONSTRATION_HEAL) {
        ui->demonstrationLabel->setStyleSheet("QLabel{font-size: 40px;"
                                              "color: green}");
        demonstration += "+";
    }
    demonstration += QString::number(amount);
    ui->demonstrationLabel->setText(demonstration);
    ui->demonstrationLabel->raise();
    ui->demonstrationLabel->show();
    //需要自己关闭
}
void battleWidget::keyPressEvent(QKeyEvent *event)       // 键盘按下事件
{
    switch (event->key()) {
        //1:普通攻击
        case Qt::Key_1:
            on_baseAttackButton_clicked();
            break;
        //2:技能1
        case Qt::Key_2:
            on_skill1Button_clicked();
            break;
        //3:技能2
        case Qt::Key_3:
            on_skill2Button_clicked();
            break;
        //4:技能3
        case Qt::Key_4:
            on_skill3Button_clicked();
            break;
       //Backspace:逃跑
        case Qt::Key_Backspace:
            on_fleedButton_clicked();
            break;
    }
}
