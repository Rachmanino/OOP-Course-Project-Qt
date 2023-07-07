#include "soundeffectpalyer.h"

soundEffectPalyer::soundEffectPalyer()
{
    this->audioOutput = new QAudioOutput;
    this->mediaPlayer = new QMediaPlayer;
    mediaPlayer->setLoops(1);
}
soundEffectPalyer::~soundEffectPalyer()
{
    delete this->audioOutput;
    delete this->mediaPlayer;
}

void soundEffectPalyer::playMusic(QString musicName, int volume)
{
    //mediaPlayer->stop();
    if (musicName != lastEffect)
    {
        mediaPlayer->setSource(QUrl::fromLocalFile("../wuyu/music/" + musicName + ".mp3"));
        lastEffect = musicName;
    }
    audioOutput->setVolume(volume);
    // qDebug() <<  mediaPlayer->hasAudio() <<mediaPlayer->source();
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->play();
}
void soundEffectPalyer::stopMusic()
{
    mediaPlayer->stop();
}
