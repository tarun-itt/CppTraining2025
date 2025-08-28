#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

#include "PlaylistWriter.h"
#include "SongData.h"

class GivenTestingPlaylistWriter : public ::testing::Test {
protected:
    std::string testDir;
    PlaylistWriter* playlistWriter;
    std::string playlistName = "Test Playlist";
    std::vector<std::string> songIds = {"songID1", "songID2", "songID3"};

    std::vector<SongData> songData = {
        {"xyz", "Track Rambo", "Artist Panda", "path/to/rambo.mp3"},
        {"abc", "Track Freestyle", "Artist Lion", "path/to/freestyle.mp3"},
        {"def", "Track Dance", "Artist Tiger", "path/to/dance.mp3"}
    };
    

    void SetUp() override {
        testDir = "../playlists";
        playlistWriter = new PlaylistWriter(testDir);
    }

    void TearDown() override {
        delete playlistWriter;
        std::filesystem::remove_all(testDir);
    }

};

TEST_F(GivenTestingPlaylistWriter, whenSavePlaylist_thenPlaylistSaved) {
    playlistWriter->save(songIds, playlistName);

    try{
        std::ifstream file(testDir + "/" + playlistName + ".txt");
        std::string line;
        int i = 0;

        while (std::getline(file, line)) {
            EXPECT_EQ(line, songIds[i]);
            i++;
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

TEST_F(GivenTestingPlaylistWriter, whenLoadPlaylist_thenPlaylistLoaded) {
    playlistWriter->save(songIds, playlistName);

    std::vector<std::string> loadedSongIds = playlistWriter->load(playlistName);
    EXPECT_EQ(loadedSongIds[0], songIds[0]);
    EXPECT_EQ(loadedSongIds[1], songIds[1]);
    EXPECT_EQ(loadedSongIds[2], songIds[2]);
}

TEST_F(GivenTestingPlaylistWriter, whenDeletePlaylist_thenPlaylistDeleted) {
    playlistWriter->save(songIds, playlistName);
    EXPECT_EQ(playlistWriter->load(playlistName).size(), 3);

    playlistWriter->deletePlaylist(playlistName);
    EXPECT_EQ(playlistWriter->load(playlistName).size(), 0);
}