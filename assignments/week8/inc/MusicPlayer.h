#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "IAudioManager.h"
#include "IPlaylist.h"
#include "ISongLibrary.h"
#include "IMusicPlayer.h"

class MusicPlayer : public IMusicPlayer {
private:
    IAudioManager& audioManager;
    IPlaylist* playlist = nullptr;
    ISongLibrary& songLibrary;  
    enum class State { STOPPED, PLAYING, PAUSED };
    State state = State::STOPPED;

public:
    MusicPlayer(IAudioManager& player, ISongLibrary& library);

    void setPlaylist(IPlaylist* newPlaylist);
    void play();
    void pause();
    void resume();
    void stop();
    void next();
    void previous();
    bool isPlaying() const;
    bool isPaused() const;
};

#endif