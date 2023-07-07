#include "fadelabel.h"
#include "characterslices.h"

fadeLabel::fadeLabel(QWidget* parent):
    QLabel(parent)
{
    this->resize(parent->size());
    this->move(0, 0);
    this->setStyleSheet("background-color:rgba(0, 0, 0, 1)");
    this->hide();
}

void fadeLabel::fadeIn()
{
    this->show();
    for (int i = 100; i >= 0; --i)
    {
        this->setStyleSheet("background-color:rgba(0, 0, 0, "+QString::number(i/(double)100)+")");
        CharacterSlices::delay(FADELABEL_DELAYTIME);
    }
    this->hide();
}

void fadeLabel::fadeOut()
{
    this->show();
    for (int i = 0; i <= 100; ++i)
    {
        this->setStyleSheet("background-color:rgba(0, 0, 0, "+QString::number(i/(double)100)+")");
        CharacterSlices::delay(FADELABEL_DELAYTIME);
    }
    this->hide();
}
