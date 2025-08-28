#ifndef SONGLIBRARY_H
#define SONGLIBRARY_H

#include <unordered_map>
#include <string>

#include "ISongLibrary.h"

class SongLibrary : public ISongLibrary {
private:
    std::unordered_map<std::string, SongData> songs;

public:
    SongLibrary() = default;
    SongLibrary(const std::string& filename);
    
    SongData getSong(const std::string& id) const override;
    std::vector<SongData> getAllSongs() const override;
    bool hasSong(const std::string& id) const override;
    void loadSongsFromFile(const std::string& filename);
};

#endif