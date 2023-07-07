//Completed by 商邑飞

#ifndef SOUNDEFFECTPALYER_H
#define SOUNDEFFECTPALYER_H

#include "QtMultimedia"


class soundEffectPalyer
{
public:
    soundEffectPalyer();
    ~soundEffectPalyer();

    QAudioOutput* audioOutput;
    QMediaPlayer* mediaPlayer;
    QString lastEffect;//如果重复用playmusic放同一个音效会出问题，这个变量是为了避免这个问题

    void playMusic(QString musicName, int volume = 50);
    void stopMusic();
};

#endif // SOUNDEFFECTPALYER_H
