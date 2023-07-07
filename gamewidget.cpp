
#include "gamewidget.h"

gameWidget::gameWidget(QWidget *parent)
    : QWidget{parent}
    , ui(new gameWidget), charaPic(DEFAULT_PIC_PATH, 7), isWalking(false)
{
    this->setWindowTitle("地图：村庄");
    this->setFixedSize(960, 640);
    QPalette palette;
    QImage image("../wuyu/images/mapWidget/village.png");
    palette.setBrush(this->backgroundRole(), QBrush(image));
    this->setPalette(palette);

    /* test:
    Hero h(1,2,3,4,"刘宗熹",new Weapon(5,6,7,8,"大宝剑","专为舞者设计！"));
    h.PrintInfo();
    */

}

void gameWidget::CharaterWalk(const QString & direct)//向指定的方向行走
{
    if (isWalking)
        return;
    isWalking = true;//防止在一个走路动作结束前连续按走路导致bug
    //QLabel & lb = *(ui->Character);
    QString direction = direct.toLower();//转小写，方便识别
    //QPoint position = lb.pos();
    QPoint delta;
    int ptr;//所需差分的下标
    int originalP;

    if (direction == "left")
    {
        ptr = charaPic.standFaceLeft;
        delta = QPoint(-CHARATER_STEP_LENGTH, 0);
    }
    else if(direction == "right")
    {
        ptr = charaPic.standFaceRight;
        delta = QPoint(CHARATER_STEP_LENGTH, 0);
    }
    else if (direction == "up")
    {
        ptr = charaPic.standFaceUp;
        delta = QPoint(0, -CHARATER_STEP_LENGTH);
    }
    else if (direction == "down")
    {
        ptr = charaPic.standFaceDown;
        delta = QPoint(0, CHARATER_STEP_LENGTH);
    }
    else
    {
        qDebug() << "Wrong direction!";//如果方向输入错误，直接返回，debuglog
        return;
    }
    originalP = ptr;

    for (int i = 0; i < CHARATER_APPLY_SIZE/CHARATER_STEP_LENGTH; ++i)
    {
        lb.setPixmap(charaPic.slices[ptr]);
        ptr += 4;//距离下一个差分是4
        ptr = ptr % 12;//一共12个差分，防止下标越界
        position += delta;//位置向指定方向移动一步
        lb.move(position);//移动标签
        lb.show();
        charaPic.delay(100);//delay一下，以便看清动画
    }
    lb.setPixmap(charaPic.slices[originalP]);
    isWalking = false;
}


