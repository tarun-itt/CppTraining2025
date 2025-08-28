#ifndef IPLAYLIST_H
#define IPLAYLIST_H

#include <string>
#include <vector>

class IPlaylist {
public:
    virtual ~IPlaylist() = default;
    virtual void addSong(const std::string& id) = 0;
    virtual void removeSong(int index) = 0;
    virtual void moveUp(int index) = 0;
    virtual void moveDown(int index) = 0;
    virtual std::string next() = 0;
    virtual std::string previous() = 0;
    virtual std::string getCurrent() const = 0;
    virtual std::string getName() const = 0;
    virtual std::vector<std::string> getSongs() const = 0;
    virtual void setCurrentIndex(int index) = 0;
    virtual int getCurrentIndex() const = 0;
};

#endif