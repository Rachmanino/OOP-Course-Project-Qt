//Completed by 魏甬翔

#ifndef ATKANIMATION_H
#define ATKANIMATION_H

#define WEAPON_PIC_WIDTH 192
#define WEAPON_PIC_HEIGHT 192
#define WEAPON_APPLY_SIZE 192
//#define WEAPON_STEP_LENGTH 100
#define GRID_SIZE 32    //格点大小
#define DEFAULT_DELAY 50
//#define DEFAULT_PICID 1

#include "QPixmap"
#include "QDebug"
#include "QLabel"
#include "QTime"
#include "QCoreApplication"

class atkAnimation
{
public :
    QWidget* parent;
    QPixmap slices[40];
    atkAnimation(const QString& Path, QWidget* parent, int applySize = WEAPON_APPLY_SIZE);
    void atkEffection(int x, int y, int head, int tail, int perDelay);
};

#endif // ATKANIMATION_H
