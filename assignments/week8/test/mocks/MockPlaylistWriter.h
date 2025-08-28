#include <gmock/gmock.h>

#include "IPlaylistWriter.h"

class MockPlaylistStorage : public IPlaylistWriter {
public:
    MOCK_METHOD(void, save, (const std::vector<std::string>& songs, const std::string& name), (override));
    MOCK_METHOD(std::vector<std::string>, load, (const std::string& name), (override));
    MOCK_METHOD(std::vector<std::string>, getAllPlaylists, (), (const, override));
}; 