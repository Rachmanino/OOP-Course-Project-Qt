//Completed by 吴童

#ifndef MYMUSICPLAYER_H
#define MYMUSICPLAYER_H

#include <QtMultimedia>

#define DEFAULT_VOLUME 50

class myMusicPlayer
{
public:
    myMusicPlayer();

    static QAudioOutput* audioOutput;
    static QMediaPlayer* mediaPlayer;

    static void playMusic(QString musicName, int volume = DEFAULT_VOLUME);
    static void stopMusic();
};

#endif // MYMUSICPLAYER_H
