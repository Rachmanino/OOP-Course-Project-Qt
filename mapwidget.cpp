//Completed by 商邑飞 and 吴童

#include "mapwidget.h"
#include "ui_mapwidget.h"
#include "battlewidget.h"
#include "mymusicplayer.h"
#include "fadelabel.h"
#include "fstream"

#include<time.h>
#include<stdlib.h>

#define maxX 30
#define maxY 20
#define IniDir CharacterSlices::standFaceRight  //默认方向（6）

#define PROFILE_X 138
#define PROFILE_Y 103 //头像左上角位置

#define ORDINARY_GRID 1

//typedef std::pair<Monster, QLabel*> monsterEntity;


int posX, posY, dir;
int pass[maxX][maxY];
Monster* monsterMap[maxX][maxY] = {nullptr};//存储怪物的位置、数值等信息与对应的label
std::string mapTitle;
//QString mapName;

bool isCheckingInfo;
QLabel *info, *profile;

QString mapWidget::mapNames[] = {"", "", "village", "dungeon", "room"};
    //village:2
    //dungeon:3
    //room:4

mapWidget::mapWidget(QWidget *parent, Hero* _hero, mainWidget* mw) :
    QWidget(parent),
    hero(_hero),
    ui(new Ui::mapWidget), charaPic(DEFAULT_PIC_PATH, hero->picId), isWalking(false)
{
    //窗口初始化
    ui->setupUi(this);
    this->setFixedSize(GRID_SIZE*maxX, GRID_SIZE*maxY);
    this->setMainMenu(mw);

    //角色初始化
    ui->Character->resize(CHARATER_APPLY_SIZE, CHARATER_APPLY_SIZE);

    isCheckingInfo = false;

    info = new QLabel(this);
    profile = new QLabel(this);

    ui->atkLabel->hide();
    ui->magLabel->hide();
    ui->defLabel->hide();
    ui->hpLabel->hide();
}

void mapWidget::setMainMenu(mainWidget* mw)
{
    mainMenu = mw;
}

void mapWidget::produceData(const QString mapName) {    //mapTitle，初始位置，dir需要手动录入
    //用法：需要注释
    //可以选择在终端or直接重定向到txt
    std::string dataPath = "../wuyu/data/mapWidget/" + mapName.toStdString() + ".txt";
    // qDebug() << dataPath;
    // freopen(dataPath.c_str(),"w",stdout);
    for (int i=0;i<maxX;i++) {
        for (int j=0;j<maxY;j++) {
            std::cout << pass[i][j] << ' ';
            // if (pass[i][j]) qDebug()<<i<<j;
        }
        std::cout << std::endl;
    }
}

void clearMonster(int x, int y)
{
    if (monsterMap[x][y] == nullptr)
        return;
    delete monsterMap[x][y];
    monsterMap[x][y] = nullptr;
}
void clearAllMonsters()
{
    for (int i = 0; i < maxX; ++i)
        for (int j = 0; j < maxY; ++j)
            clearMonster(i,j);
}//清除地图上所有的怪物
void mapWidget::killMonster()
{
    clearMonster(posX, posY);
}

void mapWidget::generateMonsters (int num) {
    int cnt = 0;
    srand(time(0));
    CharacterSlices slime("../wuyu/images/character/Monster.png", 3);
    CharacterSlices bat("../wuyu/images/character/Monster.png", 1);
//    QLabel* testlb = new QLabel(this);
//    testlb->setPixmap(slime.slices[slime.standFaceDown]);
//    testlb->resize(CHARATER_APPLY_SIZE, CHARATER_APPLY_SIZE);
//    testlb->move(32, 32);
    while (cnt < num) {
        for (int i = 0; i < 30; ++i)
            for (int j = 0; j < 20; ++j)
            {
                if (cnt >= num)break;
                if (pass[i][j] != ORDINARY_GRID)
                    continue;
                if (std::abs(i-posX) <= 2 && std::abs(j-posY) <= 2)
                    continue;
                if (monsterMap[i][j] != nullptr)
                    continue;
                if (rand()%20 == 0)
                {
                    QLabel* t = new QLabel(this);
                    if (rand()%2)
                    {
                        monsterMap[i][j] = new Monster(80,20,5,4,"Slime",t);
                        t->setPixmap(slime.slices[slime.standFaceDown + rand()%4]);
                    }
                    else
                    {
                        monsterMap[i][j] = new Monster(60,40,0,5,"Bat",t);
                        t->setPixmap(bat.slices[bat.standFaceDown + rand()%4]);
                    }
                    t->resize(CHARATER_APPLY_SIZE, CHARATER_APPLY_SIZE);
                    t->move(i*GRID_SIZE-2, j*GRID_SIZE-2);
                    t->lower();
                    t->show();
                    ++cnt;
                }
            }
    }//while
}

void MonsterRandomTurn()//怪物随机转向
{
    CharacterSlices slime("../wuyu/images/character/Monster.png", 3);
    CharacterSlices bat("../wuyu/images/character/Monster.png", 1);
    srand(time(0));
    for (int i = 0; i < maxX; ++i)
        for (int j = 0; j < maxY; ++j)
        {
            if (monsterMap[i][j] == nullptr)
                continue;
            if (rand()%3 == 0)
            {
                if (monsterMap[i][j]->name == "Slime")
                    monsterMap[i][j]->tachie->setPixmap(slime.slices[rand()%4+slime.standFaceDown]);
                else
                    monsterMap[i][j]->tachie->setPixmap(bat.slices[rand()%4+bat.standFaceDown]);
            }
        }
}

void mapWidget::load(const QString _mapName) {
    clearAllMonsters();//清除地图上的所有怪物
    mapName = _mapName; //mapName存在程序全局变量中
    qDebug() << _mapName << "loaded!";

    std::string dataPath = "../wuyu/data/mapWidget/" + mapName.toStdString() + ".txt";
    // qDebug() << dataPath;
    std::fstream is(dataPath);
    is >> mapTitle;
    is >> posX >> posY >> dir;
    for (int i=0;i<maxX;i++) {
        for (int j=0;j<maxY;j++) {
            is >> pass[i][j];
            // if (pass[i][j]) qDebug()<<i<<j;
        }
    }
    //qDebug() << mapTitle;

    //初次设定地图链接处使用，后续可删掉
    /*
    if (_mapName == "village")
        pass[10][11] = 3;
    if (_mapName == "dungeon")
        pass[10][19] = 2;
    */

    /*
    if (_mapName == "village")
        pass[19][2] = pass[20][2] = 4;
    if (_mapName == "room")
        pass[15][19] = 2;
    */

    ui->Character->move(posX*GRID_SIZE, posY*GRID_SIZE+BIAS_Y);
    ui->Character->setPixmap(charaPic.slices[dir]);

    this->setWindowTitle(QString::fromStdString(mapTitle));

    QPalette palette;
    QString mapPath = "../wuyu/images/mapWidget/" + mapName + ".png";
    // qDebug() << mapPath;
    QImage image(mapPath);
    palette.setBrush(this->backgroundRole(), QBrush(image));

    this->setPalette(palette);
    if (mapName == "dungeon")
        generateMonsters();

    myMusicPlayer::playMusic(mapName);
}

void mapWidget::save () {
    qDebug() << mapName << "saved!";
    std::string dataPath = "../wuyu/data/mapWidget/" + mapName.toStdString() + ".txt";
    // qDebug() << dataPath;
    std::fstream os(dataPath);
    os << mapTitle << std::endl;
    os << posX <<' '<< posY << ' ' << dir << std::endl;
    for (int i=0;i<maxX;i++) {
        for (int j=0;j<maxY;j++) {
            os << pass[i][j] << ' ';
            // if (pass[i][j]) qDebug()<<i<<j;
        }
        os << std::endl;
    }
    /*if (os.good()) qDebug() << "Freopen successfully!"*/;
    std::fstream _os("../wuyu/data/hero/hero.txt", std::ios::out|std::ios::trunc);  //ios::out和ios::trunc需要同时设置才能覆写！
    //if (_os.good())qDebug() << "os good and" << mapName << "saved";
    _os<<mapName.toStdString()<<std::endl;
    _os<<hero->maxHp<<' '<<hero->hp<<' '<<hero->atk<<' '<<hero->def<<' '<<hero->mag<<' '<<hero->name.toStdString();

    myMusicPlayer::stopMusic();
}

mapWidget::~mapWidget()
{
    delete ui;
}

void mapWidget::CharacterWalk(const QString & direct)//向指定的方向行走
{
    if (isWalking)
        return;

    isWalking = true;//防止在一个走路动作结束前连续按走路导致bug

    QLabel & lb = *(ui->Character);
    QString direction = direct.toLower();//转小写，方便识别
    QPoint position = lb.pos();
    QPoint delta;
    int ptr;//所需差分的下标

    if (direction == "left")
    {
        posX--;
        ptr = charaPic.standFaceLeft;
        delta = QPoint(-CHARATER_STEP_LENGTH, 0);
    }
    else if(direction == "right")
    {
        posX++;
        ptr = charaPic.standFaceRight;
        delta = QPoint(CHARATER_STEP_LENGTH, 0);
    }
    else if (direction == "up")
    {
        posY--;
        ptr = charaPic.standFaceUp;
        delta = QPoint(0, -CHARATER_STEP_LENGTH);
    }
    else if (direction == "down")
    {
        posY++;
        ptr = charaPic.standFaceDown;
        delta = QPoint(0, CHARATER_STEP_LENGTH);
    }
    else
    {
        //qDebug() << "Wrong direction!";//如果方向输入错误，直接返回，debuglog
        return;
    }
    dir = ptr;
    for (int i = 0; i < GRID_SIZE/CHARATER_STEP_LENGTH; ++i)
    {
        ptr += 4;//距离下一个差分是4
        ptr = ptr % 12;//一共12个差分，防止下标越界
        lb.setPixmap(charaPic.slices[ptr]);
        position += delta;//位置向指定方向移动一步
        lb.move(position);//移动标签
        lb.show();
        charaPic.delay();//delay一下，以便看清动画
    }
    lb.setPixmap(charaPic.slices[dir]);
    isWalking = false;

    //与怪物的encounter
    if (monsterMap[posX][posY] != nullptr)
    {
        battleWidget* bw = new battleWidget(nullptr, hero, monsterMap[posX][posY]);
        bw->setMap(this);
        //this->save();//不保存，直接load村庄即可
        fadeLabel f(this);
        f.fadeOut();
        this->hide();
        bw->show();
        fadeLabel g(bw);
        g.fadeIn();
    }

    // pass[posX][posY] = 1;
    //qDebug() << posX << posY << direction;
}

bool mapWidget::admissible (int newX, int newY) {
    //qDebug ()<< newX << newY << pass[newX][newY];
    return    newX>=0
           && newX<maxX
           && newY>=0
           && newY<maxY
           && pass[newX][newY];
}

void mapWidget::keyPressEvent(QKeyEvent *event)       // 键盘按下事件
{

    //if (rand()%2)
        MonsterRandomTurn();//每次操作都有机会让随机怪物转向
    fadeLabel f(this);
    fadeLabel g(mainMenu);
    switch (event->key()) {
        //Esc退出游戏
        case Qt::Key_Escape:
            this->save();
            f.fadeOut();
            this->close();
            break;
        //Backspace回到主页面
        case Qt::Key_Backspace:
            this->save();
            f.fadeOut();
            this->close();
            mainMenu->show();
            g.fadeIn();
            myMusicPlayer::playMusic("mainWidget");
            break;

        //WASD or 上下左右 控制方向
        case Qt::Key_Up:
        case Qt::Key_W:
            ui->Character->setPixmap(charaPic.slices[charaPic.standFaceUp]);
            if (admissible(posX, posY-1) && !isCheckingInfo) {
                //if (event->isAutoRepeat()) return;
                CharacterWalk("up");    //此处posX和posY已经改变，后续直接使用即可！
                if (pass[posX][posY] != ORDINARY_GRID) {
                        save();
                        charaPic.delay();
                        //qDebug() << "not right!";
                        f.fadeOut();
                        load(mapNames[ pass[posX][posY] ]);
                        f.fadeIn();
                }
            }
            break;
        case Qt::Key_Left:
        case Qt::Key_A:
            ui->Character->setPixmap(charaPic.slices[charaPic.standFaceLeft]);
            if (admissible(posX-1, posY) && !isCheckingInfo) {
                //if (event->isAutoRepeat()) return;
                CharacterWalk("left");
                if (pass[posX][posY] != ORDINARY_GRID) {
                    save();
                    charaPic.delay();
                    //qDebug() << "not right!";
                    f.fadeOut();
                    load(mapNames[ pass[posX][posY] ]);
                    f.fadeIn();
                }
            }
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
            ui->Character->setPixmap(charaPic.slices[charaPic.standFaceRight]);
            if (admissible(posX+1, posY) && !isCheckingInfo) {
                //if (event->isAutoRepeat()) return;
                CharacterWalk("right");
                if (pass[posX][posY] != ORDINARY_GRID) {
                    save();
                    charaPic.delay();
                    //qDebug() << "not right!";
                    f.fadeOut();
                    load(mapNames[ pass[posX][posY] ]);
                    f.fadeIn();
                }
            }
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
            ui->Character->setPixmap(charaPic.slices[charaPic.standFaceDown]);
            if (admissible(posX, posY+1) && !isCheckingInfo) {
                //if (event->isAutoRepeat()) return;
                CharacterWalk("down");
                if (pass[posX][posY] != ORDINARY_GRID) {
                    save();
                    charaPic.delay();
                    //qDebug() << "not right!";
                    f.fadeOut();
                    load(mapNames[ pass[posX][posY] ]);
                    f.fadeIn();
                }
            }
            break;

        //I打开和关闭信息栏
        case Qt::Key_I:
            if (event->isAutoRepeat()) return;
            if (!isCheckingInfo) {  //打开
                isCheckingInfo = true;

                QPixmap Info;
                Info.load("../wuyu/images/bag/bag.png");
                info->setFixedSize(720, 480);
                info->setPixmap(Info);
                info->move(120, 80);
                info->show();

                //QPixmap Profile = charaPic.slices[CharacterSlices::standFaceDown];
                QPixmap Profile = charaPic.face;
                profile->setFixedSize(FACE_APPLY_SIZE, FACE_APPLY_SIZE);
                profile->setPixmap(Profile);
                profile->move(PROFILE_X, PROFILE_Y);
                profile->show();

                ui->atkLabel->setStyleSheet("color:rgb(153, 62, 13);");
                ui->atkLabel->setText(QString::number(hero->atk));
                ui->magLabel->setStyleSheet("color:rgb(58, 201, 230);");
                ui->magLabel->setText(QString::number(hero->mag));
                ui->defLabel->setStyleSheet("color:rgb(168, 168, 168);");
                ui->defLabel->setText(QString::number(hero->def));
                ui->hpLabel->setStyleSheet("color:green;");
                ui->hpLabel->setText(QString::number(hero->hp)+"/"+QString::number(hero->maxHp));
                ui->atkLabel->raise();
                ui->atkLabel->show();
                ui->magLabel->raise();
                ui->magLabel->show();
                ui->defLabel->raise();
                ui->defLabel->show();
                ui->hpLabel->raise();
                ui->hpLabel->show();


            } else {    //关闭
                isCheckingInfo = false;

                info->close();
                profile->close();

                ui->atkLabel->hide();
                ui->magLabel->hide();
                ui->defLabel->hide();
                ui->hpLabel->hide();
            }
            break;
    }
}
