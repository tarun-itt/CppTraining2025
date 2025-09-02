#include <gmock/gmock.h>

#include "ISongLibrary.h"

class MockSongLibrary : public ISongLibrary {
public:
    MOCK_METHOD(SongData, getSong, (const std::string& id), (const, override));
    MOCK_METHOD(std::vector<SongData>, getAllSongs, (), (const, override));
    MOCK_METHOD(bool, hasSong, (const std::string& id), (const, override));
}; 