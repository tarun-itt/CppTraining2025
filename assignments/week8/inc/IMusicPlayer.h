#ifndef IMUSICPLAYER_H
#define IMUSICPLAYER_H

#include "IPlaylist.h"

class IMusicPlayer {
public:
    virtual ~IMusicPlayer() = default;
    
    virtual void setPlaylist(IPlaylist* playlist) = 0;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void stop() = 0;
    virtual void next() = 0;
    virtual void previous() = 0;
    virtual bool isPlaying() const = 0;
    virtual bool isPaused() const = 0;
};

#endif