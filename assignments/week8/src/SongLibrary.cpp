#include <vector>

#include "SongLibrary.h"

SongData SongLibrary::getSong(const std::string& id) const {
    return songs.at(id);
}

std::vector<SongData> SongLibrary::getAllSongs() const {
    std::vector<SongData> result;
    for (const auto& pair : songs) {
        result.push_back(pair.second);
    }
    return result;
}

bool SongLibrary::hasSong(const std::string& id) const {
    return songs.find(id) != songs.end();
}

void SongLibrary::addSong(const SongData& song) {
    songs[song.id] = song;
} 