//Completed by 魏甬翔

#include "helpwidget.h"
#include "ui_helpwidget.h"

#include "mainwidget.h"
#include "fadelabel.h"


helpWidget::helpWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::helpWidget)
{
    ui->setupUi(this);
    this->setFixedSize(960, 640);
    this->setWindowTitle("冒险助手");
//    QStatusBar *stBar = new QStatusBar(this);
    QLabel *label1 = new QLabel("版本号:2.1", this);
    label1->resize(200, 100);
    label1->move(550, 450);
//    stBar->addWidget(label1);
    QLabel *label2 = new QLabel("开发者:吴童、商邑飞、魏甬翔", this);
    label2->resize(200, 100);
    label2->move(740, 450);
//    stBar->addPermanentWidget(label2);
    QPalette palette;
    QImage image("../wuyu/images/helpWidget/helper2.jpg"); // 指定图片所在位置及图片名
    palette.setBrush(this->backgroundRole(), QBrush(image));
    this->setPalette(palette);


    this->show();
}

helpWidget::~helpWidget()
{
    delete ui;
}

void helpWidget::keyPressEvent(QKeyEvent *event)       // 键盘按下事件
{
    // qDebug() << "key pressed";
    mainWidget* m = new mainWidget;
    fadeLabel f(this);
    fadeLabel g(m);
    switch (event->key()) {
        //Esc退出游戏
        case Qt::Key_Escape:
            // qDebug() << "Game ended by key escape";
            f.fadeOut();
            this->close();
            break;
        //Backspace返回主页面
        case Qt::Key_Backspace:
            f.fadeOut();
            this->close();

            m->show();
            g.fadeIn();
            break;
    }
}

