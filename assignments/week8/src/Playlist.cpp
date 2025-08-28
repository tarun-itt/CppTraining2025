#include <algorithm>

#include "Playlist.h"

Playlist::Playlist(const std::string& playlistName) : name(playlistName) {}

void Playlist::addSong(const std::string& id) {
    songIds.push_back(id);
}

void Playlist::removeSong(int index) {
    if (index >= 0 && index < songIds.size()) {
        songIds.erase(songIds.begin() + index);
        if (currentIndex >= index && currentIndex > 0) {
            currentIndex--;
        }
    }
}

void Playlist::moveUp(int index) {
    if (index > 0 && index < songIds.size()) {
        std::swap(songIds[index], songIds[index - 1]);
        if (currentIndex == index) currentIndex--;
        else if (currentIndex == index - 1) currentIndex++;
    }
}

void Playlist::moveDown(int index) {
    if (index >= 0 && index < songIds.size() - 1) {
        std::swap(songIds[index], songIds[index + 1]);
        if (currentIndex == index) currentIndex++;
        else if (currentIndex == index + 1) currentIndex--;
    }
}

std::string Playlist::next() {
    if (songIds.empty()) return "";
    
    currentIndex = (currentIndex + 1) % songIds.size();
    return songIds[currentIndex];
}

std::string Playlist::previous() {
    if (songIds.empty()) return "";
    
    currentIndex = (currentIndex - 1 + songIds.size()) % songIds.size();
    return songIds[currentIndex];
}

std::string Playlist::getCurrent() const {
    if (songIds.empty()) return "";
    return songIds[currentIndex];
}

std::string Playlist::getName() const {
    return name;
}

std::vector<std::string> Playlist::getSongs() const {
    return songIds;
}

void Playlist::setCurrentIndex(int index) {
    if (index >= 0 && index < songIds.size()) {
        currentIndex = index;
    }
}

int Playlist::getCurrentIndex() const {
    return currentIndex;
} 