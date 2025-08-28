#include "PlaylistManager.h"
#include "Playlist.h"

PlaylistManager::PlaylistManager(ISongLibrary& lib, IPlaylistWriter& storage) 
    : songLibrary(lib), playlistWriter(storage) {
    loadPlaylists();
}

PlaylistManager::~PlaylistManager() {
    cleanupPlaylists();
}

void PlaylistManager::createPlaylist(const std::string& name) {
    if (playlists.find(name) == playlists.end()) {
        playlists[name] = new Playlist(name);
        setActivePlaylist(name);
    }
}

void PlaylistManager::setActivePlaylist(const std::string& name) {
    if (playlists.find(name) != playlists.end()) {
        activePlaylist = playlists[name];
    }
}

IPlaylist* PlaylistManager::getActivePlaylist() const {
    return activePlaylist;
}

std::vector<std::string> PlaylistManager::getAllPlaylistNames() const {
    std::vector<std::string> names;
    for (const auto& pair : playlists) {
        names.push_back(pair.first);
    }
    return names;
}

void PlaylistManager::saveAllPlaylists() {
    for (const auto& pair : playlists) {
        playlistWriter.save(pair.second->getSongs(), pair.first);
    }
}

void PlaylistManager::loadPlaylists() {
    auto playlistNames = playlistWriter.getAllPlaylists();
    for (const auto& name : playlistNames) {
        auto songIds = playlistWriter.load(name);
        auto playlist = new Playlist(name);
        
        for (const auto& songId : songIds) {
            if (songLibrary.hasSong(songId)) {
                playlist->addSong(songId);
            }
        }
        
        playlists[name] = playlist;
    }
    
    if (!playlists.empty() && !activePlaylist) {
        activePlaylist = playlists.begin()->second;
    }
}

void PlaylistManager::cleanupPlaylists() {
    for (auto& pair : playlists) {
        delete pair.second;
        pair.second = nullptr;
    }
    playlists.clear();
    activePlaylist = nullptr;
} 