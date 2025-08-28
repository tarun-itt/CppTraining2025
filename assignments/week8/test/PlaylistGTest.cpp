#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SongData.h"
#include "Playlist.h"

class GivenTestingPlaylist : public ::testing::Test {
protected:
    Playlist* playlist;
    SongData songData{"songID", "Test Song", "Test Artist", "/path/to/songOne.mp3"};
    SongData secondData{"songID2", "Test Song 2", "Test Artist 2", "/path/to/songTwo.mp3"};
    SongData thirdData{"songID3", "Test Song 3", "Test Artist 3", "/path/to/songThree.mp3"};

    void SetUp() override {
        playlist = new Playlist("Test Playlist");
    }

    void TearDown() override {
        delete playlist;
    }

};

TEST_F(GivenTestingPlaylist, whenPlaylistCreated_thenPlaylistIsEmpty) {
    EXPECT_EQ(playlist->getCurrent(), "");
    EXPECT_EQ(playlist->next(), "");
    EXPECT_EQ(playlist->previous(), "");
    EXPECT_EQ(playlist->getAllSongIds().size(), 0);
}

TEST_F(GivenTestingPlaylist, whenAddSong_thenSongAdded) {
    playlist->addSong(songData.id);
    EXPECT_EQ(playlist->getCurrent(), songData.id);
    EXPECT_EQ(playlist->getAllSongIds().size(), 1);
}

TEST_F(GivenTestingPlaylist, whenNavigateSongs_thenCorrectSongReturned) {
    playlist->addSong(songData.id);
    playlist->addSong(secondData.id);
    playlist->addSong(thirdData.id);
    
    EXPECT_EQ(playlist->getCurrent(), songData.id);
    EXPECT_EQ(playlist->next(), secondData.id);
    EXPECT_EQ(playlist->next(), thirdData.id);
    EXPECT_EQ(playlist->next(), songData.id);
}