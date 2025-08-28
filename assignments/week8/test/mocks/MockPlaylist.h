#include <gmock/gmock.h>

#include "IPlaylist.h"

class MockPlaylist : public IPlaylist {
public:
    MOCK_METHOD(void, addSong, (const std::string& id), (override));
    MOCK_METHOD(void, removeSong, (int index), (override));
    MOCK_METHOD(void, moveUp, (int index), (override));
    MOCK_METHOD(void, moveDown, (int index), (override));
    MOCK_METHOD(std::string, next, (), (override));
    MOCK_METHOD(std::string, previous, (), (override));
    MOCK_METHOD(std::string, getCurrent, (), (const, override));
    MOCK_METHOD(std::string, getName, (), (const, override));
    MOCK_METHOD(std::vector<std::string>, getSongs, (), (const, override));
    MOCK_METHOD(void, setCurrentIndex, (int index), (override));
    MOCK_METHOD(int, getCurrentIndex, (), (const, override));
}; 