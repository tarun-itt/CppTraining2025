#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Thermostat.h"

class MockSensor : public ISensor {
    public:
        MOCK_METHOD(int, readTemperature, (), (override));
};

class MockDeviceControl: public IDeviceControl {
    public:
        MOCK_METHOD(void, turnHeaterOn, (), (override));
        MOCK_METHOD(void, turnHeaterOff,(), (override));
        MOCK_METHOD(void, turnACOn, (), (override));
        MOCK_METHOD(void, turnACOff,(), (override));
};

class MockNotifier : public ICloudNotifier {
    public:
        MOCK_METHOD(void, notify, (Status), (override));
};


class ThermostatTest : public ::testing::Test {
    protected:
        MockSensor sensor;
        MockDeviceControl deviceControl;
        MockNotifier notifier;
        Thermostat thermostat{sensor, deviceControl, notifier};
};

TEST_F(ThermostatTest, TurnsOnHeaterWhenTooCold) {
    EXPECT_CALL(sensor, readTemperature())
        .WillOnce(::testing::Return(15));

    EXPECT_CALL(deviceControl, turnACOff());
    EXPECT_CALL(notifier, notify(Status::AC_OFF));
    EXPECT_CALL(deviceControl, turnHeaterOff());
    EXPECT_CALL(notifier, notify(Status::HEATER_OFF));

    int temperature = thermostat.controlTemperature();
    EXPECT_EQ(temperature, 15);
}
