//Completed by 商邑飞

#ifndef CHARACTERSLICES_H
#define CHARACTERSLICES_H

#define CHARATER_PIC_WIDTH 48
#define CHARATER_PIC_LENGTH 48//图片中一个角色差分的尺寸
#define CHARATER_STEP_LENGTH 8//角色走一步的步长
#define CHARATER_APPLY_SIZE 36  //角色大小略大于格点大小
#define CHARATER_FACE_SIZE 144 //角色脸的图片的大小
#define FACE_APPLY_SIZE 75//头像图片实际显示的大小
#define BIAS_Y -3       //Y方向偏移量，保证角色在格点正中
#define GRID_SIZE 32    //格点大小
#define DEFAULT_PIC_PATH "../wuyu/images/character/Actor2.png"
#define DEFAULT_FACE_PATH "../wuyu/images/faces/Actor2.png"
#define DEFAULT_DELAY 50
#define DEFAULT_PICID 1

#include "QPixmap"
#include "QDebug"
#include "QLabel"
#include "QTime"
#include "QCoreApplication"

class CharacterSlices
{
private:

public:
    static int standFaceDown;
    static int standFaceLeft;
    static int standFaceRight;
    static int standFaceUp;
    static int walkFaceDown1;
    static int walkFaceDown2;
    static int walkFaceLeft1;
    static int walkFaceLeft2;
    static int walkFaceRight1;
    static int walkFaceRight2;
    static int walkFaceUp1;
    static int walkFaceUp2;
    QPixmap slices[12];
    QPixmap face;
    CharacterSlices(const QString & picAddress = DEFAULT_PIC_PATH, int picID = DEFAULT_PICID,
                    const QString & faceAddress = DEFAULT_FACE_PATH);
    static void delay(unsigned long int delayTime = DEFAULT_DELAY);

    //第一个参数是图片的地址，第二个是图片中的哪一个图像
};

#endif // CHARACTERSLICES_H
