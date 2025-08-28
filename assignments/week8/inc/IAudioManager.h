#ifndef IAUDIOMANAGER_H
#define IAUDIOMANAGER_H

#include <string>

class IAudioManager {
public:
    virtual ~IAudioManager() = default;
    virtual void play(const std::string& path) = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void stop() = 0;
    virtual bool isPlaying() const = 0;
};

#endif