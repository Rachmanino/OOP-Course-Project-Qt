#include "atkanimation.h"
#include "characterslices.h"

atkAnimation::atkAnimation(const QString& Path, QWidget* _parent, int applySize)
{
    int ptr = 0;
    parent = _parent;
    QPixmap pic(Path);
    int X = pic.width() / 192, Y = pic.height() / 192;
//    num = (pic.size().x / 192) * (pic.size().y / 192);
//    int startX, startY;
//    startX = 0;


    for (int i = 0; i < Y; ++i)
        for (int j = 0; j < X; ++j)
        {
            int width = WEAPON_PIC_WIDTH;
            int height = WEAPON_PIC_HEIGHT;
            QRect subPic(QPoint(j * height, i * width), QPoint((j + 1) * height, (i + 1) * width));//左上角和右下角
            slices[ptr] = pic.copy(subPic);
            QSize picSize(applySize, applySize);//调整effect大小
            slices[ptr] = slices[ptr].scaled(picSize, Qt::KeepAspectRatio);
            ++ptr;
        }
}

void atkAnimation::atkEffection(int x, int y, int head, int tail, int perDelay) {
    QLabel * weapon = new QLabel(parent);
    //weapon->setParent(parent);
    weapon->resize(WEAPON_PIC_WIDTH, WEAPON_PIC_HEIGHT);
    weapon->move(x, y);
    weapon->setPixmap(slices[0]);
    weapon->show();
//    qDebug() << "进入";
//    QPoint position = weapon->pos();
    for (int i = head; i <= tail; ++i)
    {
        weapon->setPixmap(slices[i]);
        weapon->show();
        //QTime dieTime = QTime::currentTime().addMSecs(100);
        //qDebug() << "动画";
        //while (QTime::currentTime() < dieTime)
            //QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        CharacterSlices::delay(perDelay);
    }
    weapon->setPixmap(slices[0]);
    weapon->hide();
}
