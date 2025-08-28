#include <iostream>

#include "BASSAudioManager.h"
#include "bass.h"

BASSAudioManager::BASSAudioManager() {
    if (!BASS_Init(-1, 44100, 0, nullptr, nullptr)) {
        std::cout << "Failed to initialize BASS audio library." << std::endl;
    } 
}

BASSAudioManager::~BASSAudioManager() {
    cleanupBASS();
}

void BASSAudioManager::cleanupBASS() {
    if (currentStream) {
        BASS_StreamFree(currentStream);
        currentStream = 0;
    }
    BASS_Free();
}

void BASSAudioManager::play(const std::string& path) {
    stop();
    
    currentStream = BASS_StreamCreateFile(0, path.c_str(), 0, 0, BASS_STREAM_AUTOFREE);
    std::cout << "Current stream: " << currentStream << std::endl;
    if (currentStream) {
        if (BASS_ChannelPlay(currentStream, 0)) {
            playing = true;
            paused = false;
        } else {
            std::cerr << "Failed to play audio file: " << path << std::endl;
            BASS_StreamFree(currentStream);
            currentStream = 0;
        }
    } else {
        std::cerr << "Failed to load audio file:" << path << std::endl;
    }
}

void BASSAudioManager::pause() {
    if (currentStream && playing) {
        if (BASS_ChannelPause(currentStream)) {
            paused = true;
            playing = false;
        }
    }
}

void BASSAudioManager::resume() {
    if (currentStream && paused) {
        if (BASS_ChannelStart(currentStream)) {
            paused = false;
            playing = true;
        }
    }
}

void BASSAudioManager::stop() {
    if (currentStream) {
        BASS_ChannelStop(currentStream);
        BASS_StreamFree(currentStream);
        currentStream = 0;
        playing = false;
        paused = false;
    }
}

bool BASSAudioManager::isPlaying() const {
    if (currentStream) {
        return BASS_ChannelIsActive(currentStream) == BASS_ACTIVE_PLAYING;
    }
    return false;
} 