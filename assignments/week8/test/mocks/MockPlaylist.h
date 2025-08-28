#include <gmock/gmock.h>

#include "IPlaylist.h"

class MockPlaylist : public IPlaylist {
public:
    std::string name;
    MockPlaylist(const std::string& name) : name(name) {}
    MOCK_METHOD(void, addSong, (const std::string& id), (override));
    MOCK_METHOD(void, removeSong, (int index), (override));
    MOCK_METHOD(void, moveUp, (int index), (override));
    MOCK_METHOD(void, moveDown, (int index), (override));
    MOCK_METHOD(std::string, next, (), (override));
    MOCK_METHOD(std::string, previous, (), (override));
    MOCK_METHOD(std::string, getCurrent, (), (const, override));
    MOCK_METHOD(std::string, getName, (), (const, override));
    MOCK_METHOD(std::vector<std::string>, getAllSongIds, (), (const, override));
    MOCK_METHOD(void, setCurrentIndex, (int index), (override));
    MOCK_METHOD(int, getCurrentIndex, (), (const, override));
}; 