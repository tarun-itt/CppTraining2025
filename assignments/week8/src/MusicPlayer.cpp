#include "MusicPlayer.h"
#include "SongData.h"

MusicPlayer::MusicPlayer(IAudioManager& player, ISongLibrary& library) 
    : audioPlayer(player), songLibrary(library) {}

void MusicPlayer::setPlaylist(IPlaylist* newPlaylist) {
    playlist = newPlaylist;
    stop();
}

void MusicPlayer::play() {
    if (!playlist) return;
    
    std::string currentSongId = playlist->getCurrent();
    if (currentSongId.empty()) return;
    
    SongData song = songLibrary.getSong(currentSongId);
    audioPlayer.play(song.path);
    state = PLAYING;
}

void MusicPlayer::pause() {
    if (state == PLAYING) {
        audioPlayer.pause();
        state = PAUSED;
    }
}

void MusicPlayer::resume() {
    if (state == PAUSED) {
        audioPlayer.resume();
        state = PLAYING;
    }
}

void MusicPlayer::stop() {
    audioPlayer.stop();
    state = STOPPED;
}

void MusicPlayer::next() {
    if (!playlist) return;
    
    stop();
    std::string nextSongId = playlist->next();
    if (!nextSongId.empty()) {
        play();
    }
}

void MusicPlayer::previous() {
    if (!playlist) return;
    
    stop();
    std::string prevSongId = playlist->previous();
    if (!prevSongId.empty()) {
        play();
    }
}

bool MusicPlayer::isPlaying() const {
    return state == PLAYING;
}

bool MusicPlayer::isPaused() const {
    return state == PAUSED;
} 