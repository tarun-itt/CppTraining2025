#ifndef IPLAYLISTMANAGER_H
#define IPLAYLISTMANAGER_H

#include <string>
#include <vector>

#include "IPlaylist.h"

class IPlaylistManager {
public:
    virtual ~IPlaylistManager() = default;
    
    virtual void createPlaylist(const std::string& name) = 0;
    virtual void deletePlaylist(const std::string& name) = 0;
    virtual void setActivePlaylist(const std::string& name) = 0;
    virtual IPlaylist* getActivePlaylist() const = 0;
    virtual std::vector<std::string> getAllPlaylistNames() const = 0;
    virtual void saveAllPlaylists() = 0;
};

#endif