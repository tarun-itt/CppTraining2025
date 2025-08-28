#ifndef ISONGLIBRARY_H
#define ISONGLIBRARY_H

#include <string>
#include <vector>

#include "SongData.h"

class ISongLibrary {
public:
    virtual ~ISongLibrary() = default;
    virtual SongData getSong(const std::string& id) const = 0;
    virtual std::vector<SongData> getAllSongs() const = 0;
    virtual bool hasSong(const std::string& id) const = 0;
    virtual void addSong(const SongData& song) = 0;
};

#endif