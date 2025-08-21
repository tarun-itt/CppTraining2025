#include "ISensor.h"
#include "IDeviceControl.h"
#include "ICloudNotifier.h"

class Thermostat {
    private:
        ISensor& sensor;
        IDeviceControl& deviceControl;
        ICloudNotifier& cloudNotifier;

    public:
        Thermostat(ISensor& sensor, IDeviceControl& deviceControl, ICloudNotifier& cloudNotifier) : sensor(sensor), deviceControl(deviceControl), cloudNotifier(cloudNotifier) {}

        int controlTemperature() {
            int temperature = sensor.readTemperature();

            if (temperature < 14) {
                deviceControl.turnHeaterOn();
                cloudNotifier.notify(Status::HEATER_ON);
            } else if (temperature > 27) {
                deviceControl.turnACOn();
                cloudNotifier.notify(Status::AC_ON);
            }
            else {
                deviceControl.turnACOff();
                cloudNotifier.notify(Status::AC_OFF);
                deviceControl.turnHeaterOff();
                cloudNotifier.notify(Status::HEATER_OFF);
            }
        
            return temperature;
        }
};