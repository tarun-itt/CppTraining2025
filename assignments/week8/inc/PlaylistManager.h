#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include <unordered_map>
#include <string>
#include <vector>

#include "IPlaylist.h"
#include "ISongLibrary.h"
#include "IPlaylistWriter.h"
#include "IPlaylistManager.h"

class PlaylistManager : public IPlaylistManager {
private:
    std::unordered_map<std::string, IPlaylist*> playlists;
    IPlaylist* activePlaylist = nullptr;
    ISongLibrary& songLibrary;
    IPlaylistWriter& playlistWriter;

public:
    PlaylistManager(ISongLibrary& lib, IPlaylistWriter& storage);
    ~PlaylistManager();

    void createPlaylist(const std::string& name);
    void setActivePlaylist(const std::string& name);
    IPlaylist* getActivePlaylist() const;
    std::vector<std::string> getAllPlaylistNames() const;
    void saveAllPlaylists();

private:
    void loadPlaylists();
    void cleanupPlaylists();
};

#endif