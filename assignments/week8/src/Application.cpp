#include <iostream>
#include <vector>
#include <limits>
#include <string>

#include "Application.h"
#include "SongData.h"
#include "IPlaylist.h"

Application::Application(IPlaylistManager& manager, IMusicPlayer& player, ISongLibrary& library)
    : playlistManager(manager), musicPlayer(player), songLibrary(library) {}

void Application::run() {
    int choice;
    IPlaylist* activePlaylist = nullptr;

    while(true){    
        activePlaylist = playlistManager.getActivePlaylist();    
        if (activePlaylist) {
            managePlaylistMenu();
        } else {
            displayMainMenu();

            if(std::cin >> choice){
                switch (static_cast<MainMenuChoice>(choice)) {
                    case MainMenuChoice::CREATE_PLAYLIST:{
                        createPlaylist();
                        break;
                    }
                    case MainMenuChoice::SWITCH_PLAYLIST: {
                        switchPlaylist();
                        activePlaylist = playlistManager.getActivePlaylist();
                        break;
                    }
                    case MainMenuChoice::MANAGE_PLAYLIST: {
                        managePlaylistMenu();
                        activePlaylist = playlistManager.getActivePlaylist();
                        break;
                    }
                    case MainMenuChoice::EXIT: {
                        std::cout << "Bye!\n"; 
                        playlistManager.saveAllPlaylists();
                        return;
                    }
                    default: std::cout << "Invalid choice. Try again.\n";
                }
            }
            else{
                std::cout << "Invalid choice. Try again.\n";
            }
        }
    }
}

void Application::displayMainMenu() {
    std::cout << "\n=== Music Player ===\n";
    std::cout << "1. Create New Playlist\n";
    std::cout << "2. Switch Active Playlist\n";
    std::cout << "3. Manage Active Playlist\n";
    std::cout << "4. Exit\n";
    std::cout << "Choose an option: ";
}

void Application::createPlaylist() {
    std::string name;
    std::cout << "Enter playlist name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    if (!name.empty()) {
        playlistManager.createPlaylist(name);
        std::cout << "Playlist '" << name << "' created!\n";
    }
}

void Application::switchPlaylist() {
    std::vector<std::string> playlists = playlistManager.getAllPlaylistNames();
    if (!playlists.empty()) {        
        std::cout << "Available playlists:\n";

        for (int i = 0; i < playlists.size(); i++) {
            std::cout << (i + 1) << ". " << playlists[i] << "\n";
        }
        
        int choice;
        std::cout << "Select a playlist: ";
        
        if(std::cin >> choice && choice > 0 && choice <= playlists.size()) {
            playlistManager.setActivePlaylist(playlists[choice - 1]);
            musicPlayer.setPlaylist(playlistManager.getActivePlaylist());
            std::cout << "Now using '" << playlists[choice - 1] << "' playlist.\n";
        } else {
            std::cout << "Invalid selection.\n";
            std::cin.clear();
        }

    
    } else {
        std::cout << "No playlists available.\n";
        return;
    }
}

void Application::managePlaylistMenu() {
    IPlaylist* playlist = playlistManager.getActivePlaylist();
    if (!playlist) {
        std::cout << "No active playlist selected.\n";
        return;
    }
    
    int choice;
    while (true) {
        std::cout << "\n=== Playlist: " << playlist->getName() << " ===\n";
        std::cout << "1. Play/Pause\n";
        std::cout << "2. Next Song\n";
        std::cout << "3. Previous Song\n";
        std::cout << "4. Select Song to Play\n";
        std::cout << "5. Add Song\n";
        std::cout << "6. Remove Song\n";
        std::cout << "7. Move Song Up\n";
        std::cout << "8. Move Song Down\n";
        std::cout << "9. View Songs\n";
        std::cout << "10. Go to Main Menu\n";
        std::cout << "Choose an option: ";
      
        if(std::cin >> choice && choice > 0 && choice <= 10){
            switch (static_cast<PlaylistMenuChoice>(choice)) {
                case PlaylistMenuChoice::PLAY_PAUSE: {
                    if (musicPlayer.isPlaying()) {
                        musicPlayer.play();
                    } else {
                        musicPlayer.pause();
                    }
                    break;
                }
                case PlaylistMenuChoice::NEXT_SONG: {
                    musicPlayer.next();
                    break;
                }
                case PlaylistMenuChoice::PREVIOUS_SONG: {
                    musicPlayer.previous();
                    break;
                }
                case PlaylistMenuChoice::SELECT_SONG: {
                    selectSongToPlay();
                    break;
                }
                case PlaylistMenuChoice::ADD_SONG: {
                    addSongToPlaylist();
                    break;
                }
                case PlaylistMenuChoice::REMOVE_SONG: {
                    removeSongFromPlaylist();
                    break;
                }
                case PlaylistMenuChoice::MOVE_UP: {
                    moveSongInPlaylist(MoveSong::UP);
                    break;
                }
                case PlaylistMenuChoice::MOVE_DOWN: {
                    moveSongInPlaylist(MoveSong::DOWN);
                    break;
                }
                case PlaylistMenuChoice::VIEW_SONGS: {
                    viewPlaylistSongs();
                    break;
                }
                case PlaylistMenuChoice::MAIN_MENU: {
                    break;
                }
                default: std::cout << "Invalid choice. Try again.\n";
            }
            if(choice == static_cast<int>(PlaylistMenuChoice::MAIN_MENU)){
                return;
            }
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}

void Application::addSongToPlaylist() {
    IPlaylist* playlist = playlistManager.getActivePlaylist();
    auto allSongs = songLibrary.getAllSongs();
    
    if (!allSongs.empty()) {
        std::cout << "Available songs:\n";
        for (int i = 0; i < allSongs.size(); i++) {
            std::cout << (i + 1) << ". " << allSongs[i].title << " - " << allSongs[i].artist << "\n";
        }
        
        int choice;
        std::cout << "Select a song to add: ";
        
        if (std::cin >> choice && choice > 0 && choice <= allSongs.size()) {
            playlist->addSong(allSongs[choice - 1].id);
            std::cout << "Song added to playlist.\n";
        } else {
            std::cout << "Invalid selection.\n";
            std::cin.clear();
        }
        
        std::cin.ignore();
    } else {
        std::cout << "No songs available in library.\n";
    }
}

void Application::removeSongFromPlaylist() {
    IPlaylist* playlist = playlistManager.getActivePlaylist();
    auto songs = playlist->getSongs();
    
    if (!songs.empty()) {
        std::cout << "Songs in playlist:\n";
        for (int i = 0; i < songs.size(); i++) {
            SongData song = songLibrary.getSong(songs[i]);
            std::cout << (i + 1) << ". " << song.title << " - " << song.artist << "\n";
        }
        
        int choice;
        std::cout << "Select a song to remove: ";
        
        if (std::cin >> choice && choice > 0 && choice <= songs.size()) {
            musicPlayer.stop();
            playlist->removeSong(choice - 1);
            musicPlayer.play();
            std::cout << "Song removed from playlist.\n";
        } else {
            std::cout << "Invalid selection.\n";
            std::cin.clear();
        }
        
        std::cin.ignore();
    } else {
        std::cout << "Playlist is empty.\n";
    }
}

void Application::moveSongInPlaylist(enum MoveSong direction) {
    IPlaylist* playlist = playlistManager.getActivePlaylist();
    auto songs = playlist->getSongs();
    
    if (!songs.empty()) {
        std::cout << "Songs in playlist:\n";
        for (int i = 0; i < songs.size(); i++) {
            SongData song = songLibrary.getSong(songs[i]);
            std::cout << (i + 1) << ". " << song.title << " - " << song.artist << "\n";
        }
        
        int choice;
        std::cout << "Select a song to move " << (direction == MoveSong::UP ? "up" : "down") << ": ";
        
        if (std::cin >> choice && choice > 0 && choice <= songs.size()) {
            if (direction == MoveSong::UP) {
                playlist->moveUp(choice - 1);
            } else {
                playlist->moveDown(choice - 1);
            }
            std::cout << "Song moved.\n";
        } else {
            std::cout << "Invalid selection.\n";
            std::cin.clear();
        }
        
        std::cin.ignore();
    } else {
        std::cout << "Playlist is empty.\n";
    }
}

void Application::viewPlaylistSongs() {
    IPlaylist* playlist = playlistManager.getActivePlaylist();
    auto songs = playlist->getSongs();
    
    if (songs.empty()) {
        std::cout << "Playlist is empty.\n";
        return;
    }
    
    std::cout << "Songs in '" << playlist->getName() << "':\n";
    for (int i = 0; i < songs.size(); i++) {
        SongData song = songLibrary.getSong(songs[i]);
        std::cout << (i + 1) << ". " << song.title << " - " << song.artist;
        if (i == playlist->getCurrentIndex()) {
            std::cout << " [Current]";
        }
        std::cout << "\n";
    }
}

void Application::selectSongToPlay() {
    IPlaylist* playlist = playlistManager.getActivePlaylist();
    if (!playlist) {
        std::cout << "No active playlist selected.\n";
        return;
    }
    
    auto songs = playlist->getSongs();
    if (songs.empty()) {
        std::cout << "Playlist is empty. Add some songs first.\n";
        return;
    }
    
    std::cout << "Songs in playlist:\n";
    for (int i = 0; i < songs.size(); i++) {
        SongData song = songLibrary.getSong(songs[i]);
        std::cout << (i + 1) << ". " << song.title << " - " << song.artist;
        if (i == playlist->getCurrentIndex()) {
            std::cout << " [Current]";
        }
        std::cout << "\n";
    }
    
    int choice;
    std::cout << "Select a song to play: ";
    
    if (std::cin >> choice && choice > 0 && choice <= songs.size()) {
        playlist->setCurrentIndex(choice - 1);
        musicPlayer.setPlaylist(playlist);
        musicPlayer.play();
        SongData selectedSong = songLibrary.getSong(songs[choice - 1]);
        std::cout << "Now playing: " << selectedSong.title << " - " << selectedSong.artist << "\n";
    } else {
        std::cout << "Invalid selection.\n";
        std::cin.clear();
    }
    
    std::cin.ignore();
}