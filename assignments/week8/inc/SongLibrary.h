#ifndef SONGLIBRARY_H
#define SONGLIBRARY_H

#include <unordered_map>

#include "ISongLibrary.h"

class SongLibrary : public ISongLibrary {
private:
    std::unordered_map<std::string, SongData> songs;

public:
    SongData getSong(const std::string& id) const override;
    std::vector<SongData> getAllSongs() const override;
    bool hasSong(const std::string& id) const override;
    void addSong(const SongData& song) override;
};

#endif