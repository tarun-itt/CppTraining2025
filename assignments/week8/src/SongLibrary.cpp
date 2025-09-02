#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#include "SongLibrary.h"

SongLibrary::SongLibrary(const std::string& filename) {
    loadSongsFromFile(filename);
}

void SongLibrary::loadSongsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open music file: " << filename << std::endl;
        return;
    }
    
    std::string line;
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, filename_str, title, artist, path;

        std::getline(ss, id, ',');
        std::getline(ss, filename_str, ',');
        std::getline(ss, title, ',');
        std::getline(ss, artist, ',');
        
        std::getline(ss, path);

        SongData song;
        song.id = id;
        song.title = title;
        song.artist = artist;
        song.path = path;
        
        songs[id] = song;
    }
    
    file.close();
    std::cout << "Loaded " << songs.size() << " songs from " << filename << std::endl;
}

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
