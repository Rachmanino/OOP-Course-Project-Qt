//Completed by 商邑飞

#include "characterslices.h"

int CharacterSlices::standFaceDown = 4;
int CharacterSlices::standFaceLeft = 5;
int CharacterSlices::standFaceRight = 6;
int CharacterSlices::standFaceUp = 7;
int CharacterSlices::walkFaceDown1 = 0;
int CharacterSlices::walkFaceDown2 = 8;
int CharacterSlices::walkFaceLeft1 = 1;
int CharacterSlices::walkFaceLeft2 = 9;
int CharacterSlices::walkFaceRight1 = 2;
int CharacterSlices::walkFaceRight2 = 10;
int CharacterSlices::walkFaceUp1 = 3;
int CharacterSlices::walkFaceUp2 = 11;

CharacterSlices::CharacterSlices(const QString & picAddress, int picID,
                                 const QString & faceAddress)
{
    //初始化face
    QPixmap faceMap(faceAddress);
    if (faceMap.isNull())qDebug() << "error! null pixmap";
    int x = (picID-1)/2;
    int y = (picID+1)%2;
    QRect facePosition(QPoint(x*CHARATER_FACE_SIZE, y*CHARATER_FACE_SIZE),
                       QPoint((x+1)*CHARATER_FACE_SIZE, (y+1)*CHARATER_FACE_SIZE) );
    face = faceMap.copy(facePosition).scaled(QSize(FACE_APPLY_SIZE, FACE_APPLY_SIZE),
                                             Qt::KeepAspectRatio);

    int ptr = 0;
    QPixmap map(picAddress);

    int startW, startH;
    if (picID%2)
    {
        startW = (picID/2)*3;
        startH = 0;
    }
    else
    {
        startW = (picID/2 - 1)*3;
        startH = 4;
    }

    for (int i = startW; i < startW + 3; ++i)
        for (int j = startH; j < startH + 4; ++j)
        {
            int width = CHARATER_PIC_WIDTH;
            int length = CHARATER_PIC_LENGTH;
            //qDebug() << i << ' ' << j << " i and j len";
            QRect posi(QPoint(i*width, j*length), QPoint(i*width+width, j*length+length));
            slices[ptr++] = map.copy(posi);
            QSize picSize(CHARATER_APPLY_SIZE, CHARATER_APPLY_SIZE);
            slices[ptr-1] = slices[ptr-1].scaled(picSize, Qt::KeepAspectRatio);
        }
}
void CharacterSlices::delay(unsigned long int delayTime)
{
    QTime dieTime = QTime::currentTime().addMSecs(delayTime);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
}

