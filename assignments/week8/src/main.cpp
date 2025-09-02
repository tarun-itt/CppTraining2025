#include <iostream>

#include "Application.h"
#include "BASSAudioManager.h"
#include "PlaylistWriter.h"
#include "MusicPlayer.h"
#include "PlaylistManager.h"
#include "SongLibrary.h"

int main() {
    try {        
        BASSAudioManager audioManager;
        SongLibrary songLibrary("music.csv");
        PlaylistWriter playlistWriter("playlists");
    
        PlaylistManager playlistManager(songLibrary, playlistWriter);
        MusicPlayer musicPlayer(audioManager, songLibrary);

        Application app(playlistManager, musicPlayer, songLibrary);
        
        app.run();
        
    } catch (const std::exception& e) {
        std::cout << "\n Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 