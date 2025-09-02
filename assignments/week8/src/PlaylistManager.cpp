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

void PlaylistManager::deletePlaylist(const std::string& name) {
    if (playlists.find(name) != playlists.end()) {
        delete playlists[name];
        playlists.erase(name);
        playlistWriter.deletePlaylist(name);
        setActivePlaylist("");
    }
}

void PlaylistManager::setActivePlaylist(const std::string& name) {
    if(name.empty()){
        activePlaylist = nullptr;
    } else if (playlists.find(name) != playlists.end()) {
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
        playlistWriter.save(pair.second->getAllSongIds(), pair.first);
    }   
}

void PlaylistManager::loadPlaylists() {
    std::vector<std::string> playlistNames = playlistWriter.discoverPlaylists();
    for (const std::string& name : playlistNames) {
        std::vector<std::string> songIds = playlistWriter.load(name);
        IPlaylist* playlist = new Playlist(name);
        
        for (const std::string& songId : songIds) {
            if (songLibrary.hasSong(songId)) {
                playlist->addSong(songId);
            }
        }
        
        playlists[name] = playlist;
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