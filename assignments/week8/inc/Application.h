#ifndef APPLICATION_H
#define APPLICATION_H

#include "IPlaylistManager.h"
#include "IMusicPlayer.h"
#include "ISongLibrary.h"

class Application {
private:
    enum class MainMenuChoice {
        CREATE_PLAYLIST = 1,
        SWITCH_PLAYLIST,
        MANAGE_PLAYLIST,
        EXIT
    };

    enum class PlaylistMenuChoice {
        PLAY_PAUSE = 1,
        NEXT_SONG,
        PREVIOUS_SONG,
        SELECT_SONG,
        ADD_SONG,
        REMOVE_SONG,
        MOVE_UP,
        MOVE_DOWN,
        VIEW_SONGS,
        MAIN_MENU
    };

    enum class MoveSong {
        UP,
        DOWN
    };

    IPlaylistManager& playlistManager;
    IMusicPlayer& musicPlayer;
    ISongLibrary& songLibrary;

public:
    Application(IPlaylistManager& manager, IMusicPlayer& player, ISongLibrary& library);

    void run();

private:
    void displayMainMenu();
    void createPlaylist();
    void switchPlaylist();
    void managePlaylistMenu();
    void addSongToPlaylist();
    void removeSongFromPlaylist();
    void moveSongInPlaylist(MoveSong);
    void viewPlaylistSongs();
    void selectSongToPlay();


};

#endif