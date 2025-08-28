#include <iostream>

#include "MusicPlayer.h"
#include "SongData.h"

MusicPlayer::MusicPlayer(IAudioManager& player, ISongLibrary& library) 
    : audioManager(player), songLibrary(library) {}

void MusicPlayer::setPlaylist(IPlaylist* newPlaylist) {
    playlist = newPlaylist;
    stop();
}

void MusicPlayer::play() {
    if (!playlist){
        std::cout << "No playlist selected.\n";
        return;
    }
    
    std::string currentSongId = playlist->getCurrent();
    if (currentSongId.empty()){
        std::cout << "No song selected.\n";
        return;
    }

    SongData song = songLibrary.getSong(currentSongId);
    audioManager.play(song.path);
    state = State::PLAYING;
}

void MusicPlayer::pause() {
    if (state == State::PLAYING) {
        audioManager.pause();
        state = State::PAUSED;
    }
}

void MusicPlayer::resume() {
    if (state == State::PAUSED) {
        audioManager.resume();
        state = State::PLAYING;
    }
}

void MusicPlayer::stop() {
    audioManager.stop();
    state = State::STOPPED;
}

void MusicPlayer::next() {
    if (!playlist){
        std::cout << "No playlist selected.\n";
        return;
    }
    
    stop();
    std::string nextSongId = playlist->next();
    if (!nextSongId.empty()) {
        play();
    }
}

void MusicPlayer::previous() {
    if (!playlist){
        std::cout << "No playlist selected.\n";
        return;
    }
    
    stop();
    std::string prevSongId = playlist->previous();
    if (!prevSongId.empty()) {
        play();
    }
}

bool MusicPlayer::isPlaying() const {
    return state == State::PLAYING;
}

bool MusicPlayer::isPaused() const {
    return state == State::PAUSED;
} 