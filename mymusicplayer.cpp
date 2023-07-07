#include "mymusicplayer.h"

QAudioOutput* myMusicPlayer::audioOutput = new QAudioOutput;
QMediaPlayer* myMusicPlayer::mediaPlayer = new QMediaPlayer;

myMusicPlayer::myMusicPlayer()
{
    mediaPlayer->setLoops(-1);  //无限循环
}

void myMusicPlayer::playMusic(QString musicName, int volume) {
    stopMusic();    //保险起见

    mediaPlayer->setSource(QUrl::fromLocalFile("../wuyu/music/" + musicName + ".mp3"));
    audioOutput->setVolume(volume);
    // qDebug() <<  mediaPlayer->hasAudio() <<mediaPlayer->source();
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->play();
}

void myMusicPlayer::stopMusic() {
    mediaPlayer->stop();
}
