#ifndef BASSAUDIOMANAGER_H
#define BASSAUDIOMANAGER_H

#include <string>

#include "IAudioManager.h"

class BASSAudioManager : public IAudioManager {
private:
    int currentStream = 0;
    bool playing = false;
    bool paused = false;

public:
    BASSAudioManager();
    ~BASSAudioManager();
    
    void play(const std::string& path) override;
    void pause() override;
    void resume() override;
    void stop() override;
    bool isPlaying() const override;
    
private:
    void cleanupBASS();
};

#endif