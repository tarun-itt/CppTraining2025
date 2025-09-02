#ifndef STANDARDPLAYLIST_H
#define STANDARDPLAYLIST_H

#include <string>
#include <vector>

#include "IPlaylist.h"

class Playlist : public IPlaylist {
private:
    std::vector<std::string> songIds;
    int currentIndex = 0;
    std::string name;

public:
    Playlist(const std::string& playlistName);

    void addSong(const std::string& id) override;
    void removeSong(int index) override;
    void moveUp(int index) override;
    void moveDown(int index) override;
    std::string next() override;
    std::string previous() override;
    std::string getCurrent() const override;
    std::string getName() const override;
    std::vector<std::string> getAllSongIds() const override;
    void setCurrentIndex(int index) override;
    int getCurrentIndex() const override;
};

#endif