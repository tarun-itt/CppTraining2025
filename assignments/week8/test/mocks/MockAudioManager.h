#include <gmock/gmock.h>

#include "IAudioManager.h"


class MockAudioManager : public IAudioManager {
public:
    MOCK_METHOD(void, play, (const std::string& path), (override));
    MOCK_METHOD(void, pause, (), (override));
    MOCK_METHOD(void, resume, (), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(bool, isPlaying, (), (const, override));
}; 