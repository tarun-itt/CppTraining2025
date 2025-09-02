#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "MusicPlayer.h"
#include "mocks/MockAudioManager.h"
#include "mocks/MockSongLibrary.h"
#include "mocks/MockPlaylist.h"

class GivenTestingMusicPlayer : public ::testing::Test {
protected:

    MockAudioManager* mockAudioManager;
    MockSongLibrary* mockSongLibrary;
    MockPlaylist* mockPlaylist;
    MusicPlayer* musicPlayer;
    SongData songData{"songID", "Test Song", "Test Artist", "/path/to/songOne.mp3"};
    SongData songDataResult {"songID,Test Song,Test Artist,/path/to/songOne.mp3"};

    void SetUp() override {
        mockAudioManager = new MockAudioManager();
        mockSongLibrary = new MockSongLibrary();
        mockPlaylist = new MockPlaylist("Test Playlist");
        musicPlayer = new MusicPlayer(*mockAudioManager, *mockSongLibrary);
    }

    void TearDown() override {
        delete mockAudioManager;
        delete mockSongLibrary;
        delete mockPlaylist;
        delete musicPlayer;
    }
};

TEST_F(GivenTestingMusicPlayer, whenSetPlaylist_thenPlaylistUpdated) {
    EXPECT_CALL(*mockAudioManager, stop()).Times(1);
    musicPlayer->setPlaylist(mockPlaylist);
    
    EXPECT_CALL(*mockPlaylist, getCurrent()).WillOnce(::testing::Return(songDataResult.id));
    musicPlayer->play();
}

TEST_F(GivenTestingMusicPlayer, whenMusicPlayed_thenStateChanges){
    EXPECT_CALL(*mockAudioManager, play(songDataResult.path)).Times(1);
    musicPlayer->play();
    
    EXPECT_EQ(musicPlayer->isPlaying(), true);
    EXPECT_EQ(musicPlayer->isPaused(), false);
}

TEST_F(GivenTestingMusicPlayer, whenMusicPaused_thenStateChanges){
    EXPECT_CALL(*mockAudioManager, pause()).Times(1);
    musicPlayer->pause();

    EXPECT_EQ(musicPlayer->isPaused(), true);
    EXPECT_EQ(musicPlayer->isPlaying(), false);
}

TEST_F(GivenTestingMusicPlayer, whenMusicResumed_thenStateChanges){
    EXPECT_CALL(*mockAudioManager, resume()).Times(1);
    musicPlayer->resume();

    EXPECT_EQ(musicPlayer->isPlaying(), true);
    EXPECT_EQ(musicPlayer->isPaused(), false);
}

TEST_F(GivenTestingMusicPlayer, whenNextMusicPlayed_thenNextSongPlayed) {
    EXPECT_CALL(*mockPlaylist, next()).WillOnce(::testing::Return(songDataResult.id));
    EXPECT_CALL(*mockAudioManager, play(songDataResult.path)).Times(1);
    musicPlayer->next();

    EXPECT_EQ(musicPlayer->isPlaying(), true);
    EXPECT_EQ(musicPlayer->isPaused(), false);
}

TEST_F(GivenTestingMusicPlayer, whenPreviousMusicPlayed_thenPreviousSongPlayed) {
    EXPECT_CALL(*mockPlaylist, previous()).WillOnce(::testing::Return(songDataResult.id));
    EXPECT_CALL(*mockAudioManager, play(songDataResult.path)).Times(1);
    EXPECT_CALL(*mockAudioManager, stop()).Times(1);
    musicPlayer->previous();

    EXPECT_EQ(musicPlayer->isPlaying(), true);
    EXPECT_EQ(musicPlayer->isPaused(), false);
}