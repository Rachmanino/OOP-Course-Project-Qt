// Completed by 吴童

#include "mainwidget.h"
#include "helpwidget.h"
#include "ui_mainwidget.h"
#include "battlewidget.h"
#include "mapwidget.h"  //在头文件中循环include会报错
#include "mymusicplayer.h"
#include "fadelabel.h"

#include "fstream"

mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::wuyu)
{
    ui->setupUi(this);
    this->setFixedSize(960, 640);
    this->setWindowTitle(QString("新柯教吾物语：宗熹历险记"));
    QPalette palette;
    QPixmap image("../wuyu/images/mainWidget/menu.png"); // 指定图片所在位置及图片名
    image.scaled(960, 640);
    palette.setBrush(this->backgroundRole(), QBrush(image));
    this->setPalette(palette);

    myMusicPlayer::playMusic("mainWidget");
}

mainWidget::~mainWidget()
{
    delete ui;
}

void mainWidget::on_endButton_clicked()
{
    // qDebug() << "Game ended by on_endButton_clicked";
    myMusicPlayer::stopMusic();
    fadeLabel f(this);
    f.fadeOut();
    this->close();
}


void mainWidget::on_startButton_clicked()
{
    // qDebug() << "Game started by on_startButton_clicked";
    startGame();
}

void mainWidget::keyPressEvent(QKeyEvent *event)       // 键盘按下事件
{
    // qDebug() << "key pressed";
    switch (event->key()) {
        //Esc退出游戏
        case Qt::Key_Escape:
            // qDebug() << "Game ended by key escape";
            this->on_endButton_clicked();
            break;
        //Enter开始游戏
        case Qt::Key_Return:    //回车键是return，服了
            // qDebug() << "Game started by key enter";
            this->on_startButton_clicked();
            break;
        //H调出帮助界面
        case Qt::Key_H:
            //qDebug() << "Help required by Key_H!";
            this->on_helpButton_clicked();
            break;
    }
}

void mainWidget::startGame() {
    myMusicPlayer::stopMusic();
    fadeLabel f(this);
    f.fadeOut();
    this->close();

    Hero* hero = new Hero();
    std::ifstream is("../wuyu/data/hero/hero.txt");
    std::string lastMap,_name;
    is>>lastMap>>hero->maxHp>>hero->hp>>hero->atk>>hero->def>>hero->mag>>_name;
    hero->name = QString::fromStdString(_name);
//    qDebug() << "Hero created successfully!";
    mapWidget* m = new mapWidget(nullptr ,hero, this);
    m->load(QString::fromStdString(lastMap));

    //qDebug() << QString::fromStdString(lastMap);
    //m->load("village");
    //m->load("dungeon");
    // m->load("room");

    m->show();
    fadeLabel g(m);
    g.fadeIn();

    //battleWidget* b = new battleWidget();
    //b->setMap(m);
    //b->show();
}

void mainWidget::on_helpButton_clicked()
{
    myMusicPlayer::stopMusic();
    fadeLabel f(this);
    f.fadeOut();
    this->close();

    helpWidget* h = new helpWidget();
    h->show();
    fadeLabel g(h);
    g.fadeIn();
}

