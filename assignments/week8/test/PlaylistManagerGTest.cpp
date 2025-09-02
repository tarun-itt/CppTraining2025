#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "PlaylistManager.h"
#include "mocks/MockSongLibrary.h"
#include "mocks/MockPlaylistWriter.h"
#include "mocks/MockPlaylist.h"

class GivenTestingPlaylistManager : public ::testing::Test {
protected:
    MockSongLibrary* mockSongLibrary;
    MockPlaylistWriter* mockPlaylistWriter;
    MockPlaylist* mockPlaylist;
    PlaylistManager* playlistManager;

    std::string playlistNames[3] ={"Playlist1", "Playlist2", "Playlist3"};
    std::vector<std::string> songIds = {"songID1", "songID2", "songID3"};

    void SetUp() override {
        mockSongLibrary = new MockSongLibrary();
        mockPlaylistWriter = new MockPlaylistWriter();
        mockPlaylist = new MockPlaylist(playlistNames[0]);

        playlistManager = new PlaylistManager(*mockSongLibrary, *mockPlaylistWriter);
    }

    void TearDown() override {
        delete playlistManager;
        delete mockPlaylistWriter;
        delete mockSongLibrary;
        delete mockPlaylist;
    }
};

TEST_F(GivenTestingPlaylistManager, whenCreatePlaylist_thenPlaylistCreated) {
    playlistManager->createPlaylist(playlistNames[0]);

    EXPECT_EQ(playlistManager->getActivePlaylist()->getName(), playlistNames[0]);
}

TEST_F(GivenTestingPlaylistManager, whenDeletePlaylist_thenPlaylistDeleted) {
    playlistManager->createPlaylist(playlistNames[0]);
    EXPECT_EQ(playlistManager->getActivePlaylist()->getName(), playlistNames[0]);
    
    EXPECT_CALL(*mockPlaylistWriter, deletePlaylist(playlistNames[0])).Times(1);
    playlistManager->deletePlaylist(playlistNames[0]);
    
    EXPECT_EQ(playlistManager->getActivePlaylist(), nullptr);
}

TEST_F(GivenTestingPlaylistManager, whenSetActivePlaylist_thenActivePlaylistChanged) {
    playlistManager->createPlaylist(playlistNames[0]);
    playlistManager->createPlaylist(playlistNames[1]);
    EXPECT_EQ(playlistManager->getActivePlaylist()->getName(), playlistNames[1]);
    
    playlistManager->setActivePlaylist(playlistNames[0]);
    EXPECT_EQ(playlistManager->getActivePlaylist()->getName(), playlistNames[0]);
}

TEST_F(GivenTestingPlaylistManager, whenGetAllPlaylistNames_thenAllNamesReturned) {
    playlistManager->createPlaylist(playlistNames[0]);
    playlistManager->createPlaylist(playlistNames[1]);
    playlistManager->createPlaylist(playlistNames[2]);
    
    std::vector<std::string> names = playlistManager->getAllPlaylistNames();
    EXPECT_EQ(names.size(), 3);
    EXPECT_EQ(names[0], playlistNames[0]);
    EXPECT_EQ(names[1], playlistNames[1]);
    EXPECT_EQ(names[2], playlistNames[2]);
}

TEST_F(GivenTestingPlaylistManager, whenSaveAllPlaylists_thenAllPlaylistsSaved) {
    mockPlaylist->addSong(songIds[0]);
    mockPlaylist->addSong(songIds[1]);
    mockPlaylist->addSong(songIds[2]);

    playlistManager->createPlaylist(playlistNames[0]);
    
    EXPECT_CALL(*mockPlaylistWriter, save(mockPlaylist->getAllSongIds(), mockPlaylist->getName())).Times(1);
    playlistManager->saveAllPlaylists();
}